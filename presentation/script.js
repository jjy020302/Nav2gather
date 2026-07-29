/*
 * NAV2GATHER 진행 상황 공유 발표 - 슬라이드 컨트롤러
 * - 1920x1080 고정 캔버스를 뷰포트 크기에 맞춰 scale
 * - 좌우 화살표 / PageUp,Down / Space 키로 이동
 * - 하단 진행 바 + 페이지 카운터 갱신
 * - 슬라이드를 벗어나면 재생 중인 영상 일시정지
 */

(function () {
  "use strict";

  var stage = document.querySelector(".stage");
  var slides = Array.prototype.slice.call(document.querySelectorAll(".slide"));
  var total = slides.length;
  var current = 0;
  var animating = false;

  var counterEl = document.getElementById("navCounterNum");
  var progressEl = document.getElementById("navProgressBar");
  var arrowLeft = document.getElementById("arrowLeft");
  var arrowRight = document.getElementById("arrowRight");

  /* ---------------- 고정 캔버스 스케일링 ---------------- */

  function fitStage() {
    var cw = 1920, ch = 1080;
    var s = Math.min(window.innerWidth / cw, window.innerHeight / ch);
    document.documentElement.style.setProperty("--s", s.toFixed(5));
  }

  window.addEventListener("resize", fitStage);
  fitStage();

  /* ---------------- 슬라이드 전환 ---------------- */

  function pauseMediaIn(slide) {
    var vids = slide.querySelectorAll("video");
    for (var i = 0; i < vids.length; i++) {
      vids[i].pause();
    }
  }

  function updateChrome() {
    if (counterEl) {
      counterEl.textContent = String(current + 1).padStart(2, "0");
    }
    if (progressEl) {
      var pct = total > 1 ? (current / (total - 1)) * 100 : 0;
      progressEl.style.width = pct + "%";
    }
    if (arrowLeft) arrowLeft.classList.toggle("hidden", current === 0);
    if (arrowRight) arrowRight.classList.toggle("hidden", current === total - 1);
  }

  function goTo(nextIndex) {
    if (nextIndex < 0 || nextIndex >= total || nextIndex === current || animating) {
      return;
    }

    var dir = nextIndex > current ? 1 : -1;
    var from = slides[current];
    var to = slides[nextIndex];

    animating = true;

    pauseMediaIn(from);

    from.classList.remove("active");
    from.classList.add(dir > 0 ? "exit-left" : "exit-right");

    to.classList.add(dir > 0 ? "enter-right" : "enter-left");

    // 강제 리플로우 후 진입 클래스 -> active 로 전환
    void to.offsetWidth;

    requestAnimationFrame(function () {
      to.classList.add("active");
      to.classList.remove("enter-right", "enter-left");
    });

    window.setTimeout(function () {
      from.classList.remove("exit-left", "exit-right");
      animating = false;
    }, 560);

    current = nextIndex;
    updateChrome();
  }

  function next() { goTo(current + 1); }
  function prev() { goTo(current - 1); }

  /* ---------------- 초기화 ---------------- */

  var startIndex = 0;
  var hashNum = parseInt(String(window.location.hash || "").replace("#", ""), 10);
  if (!isNaN(hashNum) && hashNum >= 1 && hashNum <= total) {
    startIndex = hashNum - 1;
  }

  slides.forEach(function (slide, i) {
    slide.classList.toggle("active", i === startIndex);
  });
  current = startIndex;
  updateChrome();

  /* ---------------- 입력 처리 ---------------- */

  window.addEventListener("keydown", function (e) {
    switch (e.key) {
      case "ArrowRight":
      case "ArrowDown":
      case "PageDown":
      case " ":
        e.preventDefault();
        next();
        break;
      case "ArrowLeft":
      case "ArrowUp":
      case "PageUp":
        e.preventDefault();
        prev();
        break;
      case "Home":
        e.preventDefault();
        goTo(0);
        break;
      case "End":
        e.preventDefault();
        goTo(total - 1);
        break;
    }
  });

  if (arrowLeft) arrowLeft.addEventListener("click", prev);
  if (arrowRight) arrowRight.addEventListener("click", next);

  // 좌/우 가장자리 클릭으로도 이동 (마우스 진행용, 컨트롤 요소는 제외)
  var viewport = document.querySelector(".viewport");
  viewport.addEventListener("click", function (e) {
    if (e.target.closest(".nav-arrow, video, .code, .tbl-wrap")) return;

    var rect = viewport.getBoundingClientRect();
    var x = e.clientX - rect.left;
    if (x < rect.width * 0.12) prev();
    else if (x > rect.width * 0.88) next();
  });

  // 스와이프 (트랙패드/터치 겸용)
  var touchStartX = null;
  viewport.addEventListener("touchstart", function (e) {
    touchStartX = e.changedTouches[0].clientX;
  }, { passive: true });
  viewport.addEventListener("touchend", function (e) {
    if (touchStartX === null) return;
    var dx = e.changedTouches[0].clientX - touchStartX;
    if (Math.abs(dx) > 60) {
      if (dx < 0) next(); else prev();
    }
    touchStartX = null;
  }, { passive: true });

  /* ================================================================
     도식 화살표 자동 정렬
     - 박스의 실제 렌더링 위치/크기를 측정하여 화살표가 항상
       변(edge)의 중앙과 중앙을 연결하도록 좌표를 계산한다.
     - 텍스트 줄바꿈, 폰트 크기, 창 크기 변화에도 항상 다시 계산되므로
       하드코딩된 좌표와 달리 어긋나지 않는다.
     ================================================================ */

  function edgeAnchor(box, dx, dy, gap) {
    var halfW = box.width / 2;
    var halfH = box.height / 2;

    // 박스 중심에서 상대 박스 방향으로 향하는 직선이
    // 가로 변과 세로 변 중 어느 쪽을 먼저 통과하는지 판정
    var horizontalDominant = Math.abs(dx) * halfH > Math.abs(dy) * halfW;

    if (horizontalDominant) {
      return {
        x: box.cx + (dx > 0 ? halfW + gap : -(halfW + gap)),
        y: box.cy
      };
    }

    return {
      x: box.cx,
      y: box.cy + (dy > 0 ? halfH + gap : -(halfH + gap))
    };
  }

  function layoutBoxConnectors(container, svg, gap) {
    if (!container || !svg) return;

    var w = container.clientWidth;
    var h = container.clientHeight;
    if (!w || !h) return;

    svg.setAttribute("viewBox", "0 0 " + w + " " + h);

    var lines = svg.querySelectorAll("line[data-from][data-to]");

    lines.forEach(function (line) {
      var fromEl = document.getElementById(line.getAttribute("data-from"));
      var toEl = document.getElementById(line.getAttribute("data-to"));
      if (!fromEl || !toEl) return;

      var a = {
        width: fromEl.offsetWidth,
        height: fromEl.offsetHeight
      };
      var b = {
        width: toEl.offsetWidth,
        height: toEl.offsetHeight
      };

      // 노드는 left/top 지점에 transform:translate(-50%,-50%)로 중심을
      // 맞추므로, transform 영향을 받지 않는 offsetLeft/offsetTop 값이
      // 곧 실제 렌더링된 박스의 중심 좌표와 같다.
      a.cx = fromEl.offsetLeft;
      a.cy = fromEl.offsetTop;
      b.cx = toEl.offsetLeft;
      b.cy = toEl.offsetTop;

      var dx = b.cx - a.cx;
      var dy = b.cy - a.cy;

      var start = edgeAnchor(a, dx, dy, gap);
      var end = edgeAnchor(b, -dx, -dy, gap);

      line.setAttribute("x1", start.x.toFixed(1));
      line.setAttribute("y1", start.y.toFixed(1));
      line.setAttribute("x2", end.x.toFixed(1));
      line.setAttribute("y2", end.y.toFixed(1));
    });
  }

  function refreshDiagrams() {
    layoutBoxConnectors(
      document.getElementById("stateDiagram"),
      document.getElementById("smSvg"),
      9
    );
  }

  refreshDiagrams();
  window.addEventListener("resize", refreshDiagrams);
  window.addEventListener("load", refreshDiagrams);
  if (window.document && document.fonts && document.fonts.ready) {
    document.fonts.ready.then(refreshDiagrams);
  }
})();
