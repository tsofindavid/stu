const SPORT_DATA = {
  football: {
    name: "Football",
    facilities: {
      field1: {
        name: "Main Football Field",
        price: 50,
        times: ["09:00-11:00", "11:30-13:30", "14:00-16:00", "16:30-18:30"],
      },
      field2: {
        name: "Training Field",
        price: 30,
        times: ["10:00-12:00", "13:00-15:00", "16:00-18:00"],
      },
    },
  },
  tennis: {
    name: "Tennis",
    facilities: {
      court1: {
        name: "Center Court",
        price: 40,
        times: ["08:00-10:00", "10:30-12:30", "13:00-15:00", "15:30-17:30"],
      },
      court2: {
        name: "Training Court",
        price: 25,
        times: ["09:00-11:00", "12:00-14:00", "15:00-17:00"],
      },
    },
  },
  basketball: {
    name: "Basketball",
    facilities: {
      court1: {
        name: "Main Basketball Court",
        price: 35,
        times: ["08:30-10:30", "11:00-13:00", "14:00-16:00", "16:30-18:30"],
      },
      court2: {
        name: "Training Court",
        price: 20,
        times: ["09:30-11:30", "13:00-15:00"],
      },
    },
  },
  volleyball: {
    name: "Volleyball",
    facilities: {
      court1: {
        name: "Beach Volleyball Court",
        price: 30,
        times: ["10:00-12:00", "13:00-15:00", "16:00-18:00"],
      },
      court2: {
        name: "Indoor Court",
        price: 25,
        times: ["09:00-11:00", "12:00-14:00", "15:00-17:00"],
      },
    },
  },
};

const EQUIPMENT_PRICES = {
  ball: 5,
  shoes: 10,
};

const COUNTRY_CODES = [
  { value: "+421", label: "+421 (SK)" },
  { value: "+420", label: "+420 (CZ)" },
  { value: "+48", label: "+48 (PL)" },
  { value: "+43", label: "+43 (AT)" },
  { value: "+36", label: "+36 (HU)" },
];

const ERROR_MESSAGES = {
  REQUIRED: "This field is required",
  INVALID_EMAIL: "Please enter a valid email address",
  INVALID_PHONE: "Please enter a valid phone number",
  AGE_MISMATCH: "Age does not match birth date",
  INVALID_BIRTH_DATE: "Please enter a valid birth date",
  FUTURE_BIRTH_DATE: "Birth date cannot be in the future",
  TOO_MANY_SYMBOLS: "To many sybols",
};

const PATTERNS = {
  EMAIL: /^[a-zA-Z0-9._%+-]{3,}@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/,
  PHONE: /^[0-9]{7,15}$/,
  ICO: /^[0-9]{1,20}$/,
};

const FIELD_IDS = {
  BOOKING_FORM: "bookingForm",
  FORM_CONTAINER: "form-container",
  PREVIEW_MODAL: "previewModal",

  FIRST_NAME: "firstName",
  LAST_NAME: "lastName",
  GENDER: "gender",
  BIRTH_DATE: "birthDate",
  AGE: "age",
  EMAIL: "email",

  PHONE_CODE: "phoneCode",
  PHONE: "phone",

  SPORT: "sport",
  FACILITY: "facility",
  TIME_SLOT: "timeSlot",
  PARTICIPANTS: "participants",

  PAYMENT: "payment",
  PAYMENT_CASH: "paymentCash",
  PAYMENT_CARD: "paymentCard",
  PAYMENT_INVOICE: "paymentInvoice",
  INVOICE_FIELDS: "invoiceFields",
  COMPANY_NAME: "companyName",
  ICO: "ico",

  EQUIPMENT: "equipment",
  EQUIP_BALL: "equipBall",
  EQUIP_SHOES: "equipShoes",
  EQUIP_OTHER: "equipOther",
  EQUIP_OTHER_TEXT: "equipOtherText",

  NOTES: "notes",
  HIDDEN_FIELD: "hiddenField",
  SHOW_HIDDEN_BTN: "showHiddenBtn",

  FIRST_NAME_COUNTER: "firstNameCounter",
  LAST_NAME_COUNTER: "lastNameCounter",
  EMAIL_COUNTER: "emailCounter",
  PHONE_COUNTER: "phoneCounter",
  COMPANY_NAME_COUNTER: "companyNameCounter",
  ICO_COUNTER: "icoCounter",
  EQUIP_OTHER_TEXT_COUNTER: "equipOtherTextCounter",
  NOTES_COUNTER: "notesCounter",

  CLOSE_MODAL: "closeModal",
  SUMMARY_DITAILS: "summaryDitails",
  SUMMARY_CONTENT: "summaryContent",
  CONFIRM_SUBMIT: "confirmSubmit",
  CANCEL_SUBMIT: "cancelSubmit",
};

const REQUIRED_FIELDS_IDS = [
  FIELD_IDS.FIRST_NAME,
  FIELD_IDS.LAST_NAME,
  FIELD_IDS.GENDER,
  FIELD_IDS.BIRTH_DATE,
  FIELD_IDS.AGE,
  FIELD_IDS.EMAIL,
  FIELD_IDS.PHONE,
  FIELD_IDS.SPORT,
  FIELD_IDS.FACILITY,
  FIELD_IDS.TIME_SLOT,
];
