class SVGGame {
  constructor() {
    this.svg = document.getElementById("gameSvg");
    this.draggedElement = null;
    this.offset = { x: 0, y: 0 };
    this.isMobile = "ontouchstart" in window;

    this.init();
  }

  init() {
    this.createGameElements();
    this.setupEventListeners();
  }

  createGameElements() {
    // Create draggable shapes
    const shapes = [
      {
        id: "shape1",
        type: "circle",
        cx: 100,
        cy: 100,
        r: 40,
        fill: "#ff6b6b",
      },
      {
        id: "shape2",
        type: "rect",
        x: 200,
        y: 80,
        width: 80,
        height: 80,
        fill: "#4ecdc4",
      },
      {
        id: "shape3",
        type: "polygon",
        points: "300,100 350,50 400,100 350,150",
        fill: "#45b7d1",
      },
    ];

    shapes.forEach((shape) => {
      let element;
      switch (shape.type) {
        case "circle":
          element = document.createElementNS(
            "http://www.w3.org/2000/svg",
            "circle",
          );
          element.setAttribute("cx", shape.cx);
          element.setAttribute("cy", shape.cy);
          element.setAttribute("r", shape.r);
          break;
        case "rect":
          element = document.createElementNS(
            "http://www.w3.org/2000/svg",
            "rect",
          );
          element.setAttribute("x", shape.x);
          element.setAttribute("y", shape.y);
          element.setAttribute("width", shape.width);
          element.setAttribute("height", shape.height);
          break;
        case "polygon":
          element = document.createElementNS(
            "http://www.w3.org/2000/svg",
            "polygon",
          );
          element.setAttribute("points", shape.points);
          break;
      }

      element.setAttribute("id", shape.id);
      element.setAttribute("fill", shape.fill);
      element.classList.add("draggable");
      this.svg.appendChild(element);
    });

    // Create drop zones
    this.createDropZones();
  }

  createDropZones() {
    const dropZones = [
      { id: "zone1", cx: 500, cy: 100, r: 45 },
      { id: "zone2", cx: 600, cy: 100, width: 90, height: 90 },
      {
        id: "zone3",
        cx: 700,
        cy: 100,
        points: "700,100 750,50 800,100 750,150",
      },
    ];

    dropZones.forEach((zone) => {
      let dropZone;
      if (zone.r) {
        dropZone = document.createElementNS(
          "http://www.w3.org/2000/svg",
          "circle",
        );
        dropZone.setAttribute("cx", zone.cx);
        dropZone.setAttribute("cy", zone.cy);
        dropZone.setAttribute("r", zone.r);
      } else if (zone.width) {
        dropZone = document.createElementNS(
          "http://www.w3.org/2000/svg",
          "rect",
        );
        dropZone.setAttribute("x", zone.cx - zone.width / 2);
        dropZone.setAttribute("y", zone.cy - zone.height / 2);
        dropZone.setAttribute("width", zone.width);
        dropZone.setAttribute("height", zone.height);
      } else {
        dropZone = document.createElementNS(
          "http://www.w3.org/2000/svg",
          "polygon",
        );
        dropZone.setAttribute("points", zone.points);
      }

      dropZone.setAttribute("id", zone.id);
      dropZone.classList.add("drop-zone");
      this.svg.appendChild(dropZone);
    });
  }

  setupEventListeners() {
    if (this.isMobile) {
      // Touch events for mobile
      this.svg.addEventListener("touchstart", (e) => this.handleTouchStart(e));
      this.svg.addEventListener("touchmove", (e) => this.handleTouchMove(e));
      this.svg.addEventListener("touchend", (e) => this.handleTouchEnd(e));
    } else {
      // Mouse events for desktop
      this.svg.addEventListener("mousedown", (e) => this.handleMouseDown(e));
      this.svg.addEventListener("mousemove", (e) => this.handleMouseMove(e));
      this.svg.addEventListener("mouseup", (e) => this.handleMouseUp(e));
    }
  }

  handleMouseDown(e) {
    if (e.target.classList.contains("draggable")) {
      this.draggedElement = e.target;
      const point = this.getMousePosition(e);
      this.offset.x =
        point.x -
        parseFloat(
          this.draggedElement.getAttribute("cx") ||
            this.draggedElement.getAttribute("x"),
        );
      this.offset.y =
        point.y -
        parseFloat(
          this.draggedElement.getAttribute("cy") ||
            this.draggedElement.getAttribute("y"),
        );
    }
  }

  handleMouseMove(e) {
    if (this.draggedElement) {
      const point = this.getMousePosition(e);
      this.updateElementPosition(
        point.x - this.offset.x,
        point.y - this.offset.y,
      );
    }
  }

  handleMouseUp() {
    if (this.draggedElement) {
      this.checkDropZone();
      this.draggedElement = null;
    }
  }

  handleTouchStart(e) {
    e.preventDefault();
    if (e.target.classList.contains("draggable")) {
      this.draggedElement = e.target;
      const touch = e.touches[0];
      const point = this.getTouchPosition(touch);
      this.offset.x =
        point.x -
        parseFloat(
          this.draggedElement.getAttribute("cx") ||
            this.draggedElement.getAttribute("x"),
        );
      this.offset.y =
        point.y -
        parseFloat(
          this.draggedElement.getAttribute("cy") ||
            this.draggedElement.getAttribute("y"),
        );
    }
  }

  handleTouchMove(e) {
    e.preventDefault();
    if (this.draggedElement) {
      const touch = e.touches[0];
      const point = this.getTouchPosition(touch);
      this.updateElementPosition(
        point.x - this.offset.x,
        point.y - this.offset.y,
      );
    }
  }

  handleTouchEnd() {
    if (this.draggedElement) {
      this.checkDropZone();
      this.draggedElement = null;
    }
  }

  getMousePosition(e) {
    const CTM = this.svg.getScreenCTM();
    return {
      x: (e.clientX - CTM.e) / CTM.a,
      y: (e.clientY - CTM.f) / CTM.d,
    };
  }

  getTouchPosition(touch) {
    const CTM = this.svg.getScreenCTM();
    return {
      x: (touch.clientX - CTM.e) / CTM.a,
      y: (touch.clientY - CTM.f) / CTM.d,
    };
  }

  updateElementPosition(x, y) {
    if (this.draggedElement.tagName === "circle") {
      this.draggedElement.setAttribute("cx", x);
      this.draggedElement.setAttribute("cy", y);
    } else if (this.draggedElement.tagName === "rect") {
      this.draggedElement.setAttribute("x", x);
      this.draggedElement.setAttribute("y", y);
    } else if (this.draggedElement.tagName === "polygon") {
      // For polygons, you might want to handle translation differently
      const points = this.draggedElement.getAttribute("points").split(" ");
      const newPoints = points.map((point) => {
        const [px, py] = point.split(",").map(Number);
        return `${px + (x - parseFloat(this.draggedElement.getAttribute("data-original-x") || x))},${py + (y - parseFloat(this.draggedElement.getAttribute("data-original-y") || y))}`;
      });
      this.draggedElement.setAttribute("points", newPoints.join(" "));
    }
  }

  checkDropZone() {
    const dropZones = document.querySelectorAll(".drop-zone");
    let droppedInZone = false;

    dropZones.forEach((zone) => {
      zone.classList.remove("valid", "invalid");

      if (this.isElementInZone(this.draggedElement, zone)) {
        droppedInZone = true;
        zone.classList.add("valid");
        // Handle successful drop
        this.onSuccessfulDrop(this.draggedElement, zone);
      }
    });

    if (!droppedInZone) {
      // Return to original position or handle invalid drop
      this.returnToOriginalPosition();
    }
  }

  isElementInZone(element, zone) {
    // Implement collision detection based on element types
    // This is a simplified version - you'll need more sophisticated collision detection
    const elementRect = element.getBoundingClientRect();
    const zoneRect = zone.getBoundingClientRect();

    return !(
      elementRect.right < zoneRect.left ||
      elementRect.left > zoneRect.right ||
      elementRect.bottom < zoneRect.top ||
      elementRect.top > zoneRect.bottom
    );
  }

  onSuccessfulDrop(element, zone) {
    console.log(`Element ${element.id} dropped in zone ${zone.id}`);
    // Add your game logic here
  }

  returnToOriginalPosition() {
    // Implement return to original position logic
    console.log("Returning to original position");
  }
}

// Initialize the game when DOM is loaded
document.addEventListener("DOMContentLoaded", () => {
  new SVGGame();
});
