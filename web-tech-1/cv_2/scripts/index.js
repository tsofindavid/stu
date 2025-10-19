document.addEventListener("DOMContentLoaded", function () {
  setupCharCounters();
  setupValidation();
  setupDependentSelects();
  setupPaymentTypeToggle();
  setupEquipmentOtherToggle();
  setupHiddenField();
  setupAgeCalculation();
  setupFormSubmit();
});

// Počítadlo znakov
function setupCharCounters() {
  const fields = [
    "firstName",
    "lastName",
    "email",
    "phone",
    "companyName",
    "ico",
    "equipOtherText",
    "notes",
  ];

  fields.forEach((fieldId) => {
    const field = document.getElementById(fieldId);
    const counter = document.getElementById(fieldId + "Counter");

    if (field && counter) {
      field.addEventListener("input", function () {
        const max = this.maxLength;
        const current = this.value.length;
        counter.textContent = `${current} / ${max}`;
      });
    }
  });
}

function setupAgeCalculation() {
  const birthDateField = document.getElementById("birthDate");
  const ageField = document.getElementById("age");

  birthDateField.addEventListener("change", function () {
    if (this.value) {
      const birthDate = new Date(this.value);
      const today = new Date();
      let age = today.getFullYear() - birthDate.getFullYear();
      const monthDiff = today.getMonth() - birthDate.getMonth();

      if (
        monthDiff < 0 ||
        (monthDiff === 0 && today.getDate() < birthDate.getDate())
      ) {
        age--;
      }

      ageField.value = age;
      validateAge();
    }
  });
}

function validateAge() {
  const birthDateField = document.getElementById("birthDate");
  const ageField = document.getElementById("age");
  const ageError = document.getElementById("ageError");

  if (!birthDateField.value || !ageField.value) return false;

  const birthDate = new Date(birthDateField.value);
  const today = new Date();
  let calculatedAge = today.getFullYear() - birthDate.getFullYear();
  const monthDiff = today.getMonth() - birthDate.getMonth();

  if (
    monthDiff < 0 ||
    (monthDiff === 0 && today.getDate() < birthDate.getDate())
  ) {
    calculatedAge--;
  }

  if (parseInt(ageField.value) !== calculatedAge) {
    ageError.textContent = "Vek nezodpovedá dátumu narodenia";
    ageField.classList.add("error");
    return false;
  } else {
    ageError.textContent = "";
    ageField.classList.remove("error");
    return true;
  }
}

function validateEmail(email) {
  // Min 3 znaky pred @, min 2 domény, vrcholová doména 2-4 znaky
  const regex = /^[^\s@]{3,}@[^\s@]+\.[^\s@]+$/;

  if (!regex.test(email)) return false;

  const parts = email.split("@");
  if (parts[0].length < 3) return false;

  const domain = parts[1];
  const domainParts = domain.split(".");

  if (domainParts.length < 2) return false;

  const topDomain = domainParts[domainParts.length - 1];
  if (topDomain.length < 2 || topDomain.length > 4) return false;

  return true;
}

function validatePhone(phone) {
  return /^\d{9,15}$/.test(phone.replace(/\s/g, ""));
}

// Nastavenie validácie
function setupValidation() {
  // Email validácia
  const emailField = document.getElementById("email");
  emailField.addEventListener("blur", function () {
    const emailError = document.getElementById("emailError");
    if (this.value && !validateEmail(this.value)) {
      emailError.textContent =
        "Neplatný email (min. 3 znaky pred @, 2 domény, vrcholová doména 2-4 znaky)";
      this.classList.add("error");
    } else {
      emailError.textContent = "";
      this.classList.remove("error");
    }
  });

  // Telefón validácia
  const phoneField = document.getElementById("phone");
  phoneField.addEventListener("blur", function () {
    const phoneError = document.getElementById("phoneError");
    if (this.value && !validatePhone(this.value)) {
      phoneError.textContent = "Neplatné telefónne číslo (9-15 číslic)";
      this.classList.add("error");
    } else {
      phoneError.textContent = "";
      this.classList.remove("error");
    }
  });

  // Povinné polia
  ["firstName", "lastName", "gender", "birthDate"].forEach((fieldId) => {
    const field = document.getElementById(fieldId);
    field.addEventListener("blur", function () {
      const errorEl = document.getElementById(fieldId + "Error");
      if (!this.value) {
        errorEl.textContent = "Toto pole je povinné";
        this.classList.add("error");
      } else {
        errorEl.textContent = "";
        this.classList.remove("error");
      }
    });
  });
}

// Závislé zoznamy
function setupDependentSelects() {
  const sportSelect = document.getElementById("sport");
  const facilitySelect = document.getElementById("facility");
  const timeSlotSelect = document.getElementById("timeSlot");

  sportSelect.addEventListener("change", function () {
    facilitySelect.innerHTML = '<option value="">Vyberte priestor...</option>';
    timeSlotSelect.innerHTML =
      '<option value="">Najprv vyberte priestor</option>';
    timeSlotSelect.disabled = true;

    if (this.value && sportData[this.value]) {
      facilitySelect.disabled = false;
      const facilities = sportData[this.value].facilities;

      for (const [key, facility] of Object.entries(facilities)) {
        const option = document.createElement("option");
        option.value = key;
        option.textContent = `${facility.name} (${facility.price}€/2h)`;
        option.dataset.price = facility.price;
        facilitySelect.appendChild(option);
      }
    } else {
      facilitySelect.disabled = true;
    }
  });

  facilitySelect.addEventListener("change", function () {
    timeSlotSelect.innerHTML = '<option value="">Vyberte čas...</option>';

    if (this.value && timeSlots[this.value]) {
      timeSlotSelect.disabled = false;
      const slots = timeSlots[this.value];

      slots.forEach((slot) => {
        const option = document.createElement("option");
        option.value = slot.value;
        option.textContent = `${slot.label} ${
          slot.price > 0 ? "(+" + slot.price + "€)" : ""
        }`;
        option.dataset.price = slot.price;
        timeSlotSelect.appendChild(option);
      });
    } else {
      timeSlotSelect.disabled = true;
    }
  });
}

// Prepínanie typu platby
function setupPaymentTypeToggle() {
  const paymentRadios = document.querySelectorAll('input[name="payment"]');
  const invoiceFields = document.getElementById("invoiceFields");

  paymentRadios.forEach((radio) => {
    radio.addEventListener("change", function () {
      if (this.value === "invoice") {
        invoiceFields.classList.remove("hidden-field");
      } else {
        invoiceFields.classList.add("hidden-field");
      }
    });
  });
}

// Prepínanie "iné" vybavenie
function setupEquipmentOtherToggle() {
  const otherCheckbox = document.getElementById("equipOther");
  const otherTextField = document.getElementById("equipOtherText");
  const otherCounter = document.getElementById("equipOtherTextCounter");

  otherCheckbox.addEventListener("change", function () {
    if (this.checked) {
      otherTextField.classList.remove("hidden-field");
      otherCounter.classList.remove("hidden-field");
    } else {
      otherTextField.classList.add("hidden-field");
      otherCounter.classList.add("hidden-field");
      otherTextField.value = "";
    }
  });
}

// Skryté pole
function setupHiddenField() {
  const showBtn = document.getElementById("showHiddenBtn");
  const hiddenField = document.getElementById("hiddenField");

  showBtn.addEventListener("click", function () {
    if (hiddenField.classList.contains("hidden-field")) {
      hiddenField.classList.remove("hidden-field");
      this.textContent = "Skryť pole";
    } else {
      hiddenField.classList.add("hidden-field");
      this.textContent = "Zobraziť skryté pole";
    }
  });
}

// Odoslanie formulára
function setupFormSubmit() {
  const form = document.getElementById("bookingForm");
  const modal = document.getElementById("previewModal");
  const closeModal = document.getElementById("closeModal");
  const cancelSubmit = document.getElementById("cancelSubmit");
  const confirmSubmit = document.getElementById("confirmSubmit");

  form.addEventListener("submit", function (e) {
    e.preventDefault();

    if (validateForm()) {
      showPreview();
      modal.style.display = "block";
    }
  });

  closeModal.addEventListener("click", function () {
    modal.style.display = "none";
  });

  cancelSubmit.addEventListener("click", function () {
    modal.style.display = "none";
  });

  confirmSubmit.addEventListener("click", function () {
    form.submit();
  });

  window.addEventListener("click", function (e) {
    if (e.target === modal) {
      modal.style.display = "none";
    }
  });
}

// Validácia celého formulára
function validateForm() {
  let isValid = true;

  // Povinné polia
  const requiredFields = [
    "firstName",
    "lastName",
    "gender",
    "birthDate",
    "age",
    "email",
    "sport",
  ];

  requiredFields.forEach((fieldId) => {
    const field = document.getElementById(fieldId);
    const errorEl = document.getElementById(fieldId + "Error");

    if (!field.value) {
      errorEl.textContent = "Toto pole je povinné";
      field.classList.add("error");
      isValid = false;
    }
  });

  // Email validácia
  const email = document.getElementById("email").value;
  if (email && !validateEmail(email)) {
    document.getElementById("emailError").textContent = "Neplatný email";
    document.getElementById("email").classList.add("error");
    isValid = false;
  }

  // Vek validácia
  if (!validateAge()) {
    isValid = false;
  }

  return isValid;
}

// Zobrazenie náhľadu
function showPreview() {
  const summaryContent = document.getElementById("summaryContent");
  let totalPrice = 0;
  let html = "";

  // Osobné údaje
  html += "<h3>Osobné údaje</h3>";
  html += `<div class="summary-item"><span>Meno:</span><span>${
    document.getElementById("firstName").value
  } ${document.getElementById("lastName").value}</span></div>`;
  html += `<div class="summary-item"><span>Pohlavie:</span><span>${
    document.getElementById("gender").selectedOptions[0].text
  }</span></div>`;
  html += `<div class="summary-item"><span>Vek:</span><span>${
    document.getElementById("age").value
  } rokov</span></div>`;
  html += `<div class="summary-item"><span>Email:</span><span>${
    document.getElementById("email").value
  }</span></div>`;

  const phone = document.getElementById("phone").value;
  if (phone) {
    const phoneCode = document.getElementById("phoneCode").value;
    html += `<div class="summary-item"><span>Telefón:</span><span>${phoneCode} ${phone}</span></div>`;
  }

  // Rezervácia
  html += "<h3>Detaily rezervácie</h3>";
  const sport = document.getElementById("sport");
  const facility = document.getElementById("facility");
  const timeSlot = document.getElementById("timeSlot");

  html += `<div class="summary-item"><span>Šport:</span><span>${sport.selectedOptions[0].text}</span></div>`;

  if (facility.value) {
    const facilityPrice = parseFloat(facility.selectedOptions[0].dataset.price);
    html += `<div class="summary-item"><span>Priestor:</span><span>${facility.selectedOptions[0].text}</span></div>`;
    totalPrice += facilityPrice;
  }

  if (timeSlot.value) {
    const timePrice = parseFloat(
      timeSlot.selectedOptions[0].dataset.price || 0
    );
    html += `<div class="summary-item"><span>Čas:</span><span>${timeSlot.selectedOptions[0].text}</span></div>`;
    totalPrice += timePrice;
  }

  const participants = document.getElementById("participants").value;
  html += `<div class="summary-item"><span>Počet osôb:</span><span>${participants}</span></div>`;

  // Vybavenie
  const equipment = document.querySelectorAll(
    'input[name="equipment"]:checked'
  );
  if (equipment.length > 0) {
    html += "<h3>Vybavenie</h3>";
    equipment.forEach((item) => {
      if (item.value === "ball") {
        html += `<div class="summary-item"><span>Lopta:</span><span>5€</span></div>`;
        totalPrice += 5;
      } else if (item.value === "shoes") {
        html += `<div class="summary-item"><span>Športová obuv:</span><span>10€</span></div>`;
        totalPrice += 10;
      } else if (item.value === "other") {
        const otherText = document.getElementById("equipOtherText").value;
        html += `<div class="summary-item"><span>Iné (${otherText}):</span><span>0€</span></div>`;
      }
    });
  }

  // Platba
  const payment = document.querySelector('input[name="payment"]:checked');
  html += "<h3>Platba</h3>";
  html += `<div class="summary-item"><span>Typ platby:</span><span>${payment.labels[0].textContent}</span></div>`;

  if (payment.value === "invoice") {
    const companyName = document.getElementById("companyName").value;
    const ico = document.getElementById("ico").value;
    if (companyName)
      html += `<div class="summary-item"><span>Spoločnosť:</span><span>${companyName}</span></div>`;
    if (ico)
      html += `<div class="summary-item"><span>IČO:</span><span>${ico}</span></div>`;
  }

  // Poznámka
  const notes = document.getElementById("notes").value;
  if (notes) {
    html += "<h3>Poznámka</h3>";
    html += `<p>${notes}</p>`;
  }

  // Celková cena
  html += `<div class="summary-item summary-total"><span>Celková cena:</span><span>${totalPrice}€</span></div>`;

  summaryContent.innerHTML = html;
}
