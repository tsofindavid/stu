function initFields() {
  store[FIELD_IDS.SPORT].innerHTML = Object.keys(SPORT_DATA).reduce(
    (html, key) =>
      `${html}<option value="${key}">${SPORT_DATA[key].name}</option>`,
    '<option value="">Select sport...</option>',
  );
}

function onClickHiddenBtn() {
  if (store[FIELD_IDS.HIDDEN_FIELD].style.display === "none") {
    store[FIELD_IDS.HIDDEN_FIELD].style.display = "";
  } else {
    store[FIELD_IDS.HIDDEN_FIELD].style.display = "none";
  }
}

function onChangeEquipOther() {
  if (store[FIELD_IDS.EQUIP_OTHER].checked) {
    store[FIELD_IDS.EQUIP_OTHER_TEXT].style.display = "";
    store[FIELD_IDS.EQUIP_OTHER_TEXT_COUNTER].style.display = "";
  } else {
    store[FIELD_IDS.EQUIP_OTHER_TEXT].style.display = "none";
    store[FIELD_IDS.EQUIP_OTHER_TEXT_COUNTER].style.display = "none";
  }
}

function onChangeCount(counter, field, max) {
  store[counter].innerText = `${store[field].value.length} / ${max}`;
}

function onChangeRequired(field) {
  document.getElementById(getErrorId(field)).innerText = "";
}

function onChangeSport() {
  if (!store[FIELD_IDS.SPORT].value) {
    store[FIELD_IDS.FACILITY].innerHTML =
      '<option value="">First select sport</option>';
    store[FIELD_IDS.FACILITY].disabled = true;
    return;
  }

  store[FIELD_IDS.FACILITY].innerHTML = Object.keys(
    SPORT_DATA[store[FIELD_IDS.SPORT].value].facilities,
  ).reduce(
    (html, key) =>
      `${html}<option value="${key}">${SPORT_DATA[store[FIELD_IDS.SPORT].value].facilities[key].name}</option>`,
    '<option value="">Select facility...</option>',
  );
  store[FIELD_IDS.FACILITY].disabled = false;
}

function onChangeFacility() {
  if (!store[FIELD_IDS.SPORT].value || !store[FIELD_IDS.FACILITY].value) {
    store[FIELD_IDS.TIME_SLOT].innerHTML =
      '<option value="">First select facility</option>';
    store[FIELD_IDS.TIME_SLOT].disabled = true;
    return;
  }

  store[FIELD_IDS.TIME_SLOT].innerHTML = SPORT_DATA[
    store[FIELD_IDS.SPORT].value
  ].facilities[store[FIELD_IDS.FACILITY].value].times.reduce(
    (html, time) => `${html}<option value="${time}">${time}</option>`,
    '<option value="">Select time...</option>',
  );
  store[FIELD_IDS.TIME_SLOT].disabled = false;
}

function onCloseModal() {
  store[FIELD_IDS.PREVIEW_MODAL].style.display = "none";
}

function onSubbmitModal() {
  window.location.reload();
}

function onSubbmit(e) {
  e.preventDefault();

  const formData = new FormData(store[FIELD_IDS.BOOKING_FORM]);

  const data = {
    [FIELD_IDS.FIRST_NAME]: formData.get(FIELD_IDS.FIRST_NAME),
    [FIELD_IDS.LAST_NAME]: formData.get(FIELD_IDS.LAST_NAME),
    [FIELD_IDS.GENDER]: formData.get(FIELD_IDS.GENDER),
    [FIELD_IDS.BIRTH_DATE]: formData.get(FIELD_IDS.BIRTH_DATE),
    [FIELD_IDS.AGE]: formData.get(FIELD_IDS.AGE),
    [FIELD_IDS.EMAIL]: formData.get(FIELD_IDS.EMAIL),
    [FIELD_IDS.PHONE_CODE]: formData.get(FIELD_IDS.PHONE_CODE),
    [FIELD_IDS.PHONE]: formData.get(FIELD_IDS.PHONE),
    [FIELD_IDS.SPORT]: formData.get(FIELD_IDS.SPORT),
    [FIELD_IDS.FACILITY]: formData.get(FIELD_IDS.FACILITY),
    [FIELD_IDS.TIME_SLOT]: formData.get(FIELD_IDS.TIME_SLOT),
    [FIELD_IDS.PARTICIPANTS]: formData.get(FIELD_IDS.PARTICIPANTS) || "1",
    [FIELD_IDS.PAYMENT]: formData.get(FIELD_IDS.PAYMENT),
    [FIELD_IDS.COMPANY_NAME]: formData.get(FIELD_IDS.COMPANY_NAME) || "",
    [FIELD_IDS.ICO]: formData.get(FIELD_IDS.ICO) || "",
    [FIELD_IDS.EQUIPMENT]: formData.getAll(FIELD_IDS.EQUIPMENT),
    [FIELD_IDS.EQUIP_OTHER_TEXT]:
      formData.get(FIELD_IDS.EQUIP_OTHER_TEXT) || "",
    [FIELD_IDS.NOTES]: formData.get(FIELD_IDS.NOTES) || "",
  };

  let error = false;

  for (const field of REQUIRED_FIELDS_IDS) {
    if (!data[field]) {
      document.getElementById(getErrorId(field)).innerText =
        ERROR_MESSAGES.REQUIRED;

      error = true;
    }
  }

  const emailError = document.getElementById(getErrorId(FIELD_IDS.EMAIL));
  if (!document.getElementById(getErrorId(FIELD_IDS.EMAIL)).innerText) {
    if (!validateEmail(data[FIELD_IDS.EMAIL])) {
      emailError.innerText = ERROR_MESSAGES.INVALID_EMAIL;
      error = true;
    }
  }

  const ageError = document.getElementById(getErrorId(FIELD_IDS.AGE));
  if (!document.getElementById(getErrorId(FIELD_IDS.AGE)).innerText) {
    if (
      !validateAgeBirthDate(data[FIELD_IDS.BIRTH_DATE], data[FIELD_IDS.AGE])
    ) {
      ageError.innerText = ERROR_MESSAGES.AGE_MISMATCH;
      error = true;
    }
  }

  const phoneError = document.getElementById(getErrorId(FIELD_IDS.PHONE));
  if (!document.getElementById(getErrorId(FIELD_IDS.PHONE)).innerText) {
    if (!validatePhone(data[FIELD_IDS.PHONE])) {
      phoneError.innerText = ERROR_MESSAGES.INVALID_PHONE;
      error = true;
    }
  }

  if (!error) {
    store[FIELD_IDS.SUMMARY_DITAILS].innerHTML = Object.keys(data).reduce(
      (html, key) => `${html}<span>${key}: ${data[key]}</span>`,
      "",
    );

    let price =
      SPORT_DATA[data[FIELD_IDS.SPORT]].facilities[data[FIELD_IDS.FACILITY]]
        .price * parseInt(data[FIELD_IDS.PARTICIPANTS]);

    if (data[FIELD_IDS.EQUIP_BALL]) {
      price += 5;
    }

    if (data[FIELD_IDS.EQUIP_SHOES]) {
      price += 10;
    }

    store[FIELD_IDS.SUMMARY_CONTENT].innerHTML = `<h5>Price: ${price}</h5>`;

    store[FIELD_IDS.PREVIEW_MODAL].style.display = "";
  }
}

function initHandlers() {
  store[FIELD_IDS.SPORT].addEventListener("change", () => {
    onChangeSport();
    onChangeFacility();
  });
  store[FIELD_IDS.FACILITY].addEventListener("change", () => {
    onChangeFacility();
  });

  for (const field of REQUIRED_FIELDS_IDS) {
    store[field].addEventListener("input", () => onChangeRequired(field));
  }

  store[FIELD_IDS.FIRST_NAME].addEventListener("input", () =>
    onChangeCount(FIELD_IDS.FIRST_NAME_COUNTER, FIELD_IDS.FIRST_NAME, 50),
  );

  store[FIELD_IDS.LAST_NAME].addEventListener("input", () =>
    onChangeCount(FIELD_IDS.LAST_NAME_COUNTER, FIELD_IDS.LAST_NAME, 50),
  );

  store[FIELD_IDS.PHONE].addEventListener("input", () =>
    onChangeCount(FIELD_IDS.PHONE_COUNTER, FIELD_IDS.PHONE, 15),
  );

  store[FIELD_IDS.EQUIP_OTHER].addEventListener("change", onChangeEquipOther);
  store[FIELD_IDS.EQUIP_OTHER_TEXT].addEventListener("input", () =>
    onChangeCount(
      FIELD_IDS.EQUIP_OTHER_TEXT_COUNTER,
      FIELD_IDS.EQUIP_OTHER_TEXT,
      150,
    ),
  );

  store[FIELD_IDS.NOTES].addEventListener("input", () =>
    onChangeCount(FIELD_IDS.NOTES_COUNTER, FIELD_IDS.NOTES, 500),
  );

  store[FIELD_IDS.BOOKING_FORM].addEventListener("submit", onSubbmit);

  store[FIELD_IDS.SHOW_HIDDEN_BTN].addEventListener("click", onClickHiddenBtn);
  store[FIELD_IDS.CLOSE_MODAL].addEventListener("click", onCloseModal);
  store[FIELD_IDS.CANCEL_SUBMIT].addEventListener("click", onCloseModal);
  store[FIELD_IDS.CONFIRM_SUBMIT].addEventListener("click", onSubbmitModal);
}

document.addEventListener("DOMContentLoaded", () => {
  initStore();
  initFields();
  initHandlers();
});
