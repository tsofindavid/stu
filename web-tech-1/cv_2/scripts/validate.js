function validateRequired(value) {
  return value && value.trim() !== "";
}

function validateEmail(email) {
  const pattern = /^[a-zA-Z0-9._%+-]{3,}@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/;
  return pattern.test(email);
}

function validatePhone(phone) {
  if (!phone || phone.trim() === "") return true;
  const pattern = /^[0-9]{7,15}$/;
  return pattern.test(phone.replace(/\s/g, ""));
}

function validateAgeBirthDate(birthDate, age) {
  if (!birthDate || !age) return false;

  const birthDateObj = new Date(birthDate);
  const today = new Date();

  if (birthDateObj > today) return false;

  const calculatedAge = calculateAge(birthDateObj);
  return parseInt(age) === calculatedAge;
}

function calculateAge(birthDate) {
  const today = new Date();
  let age = today.getFullYear() - birthDate.getFullYear();
  const monthDiff = today.getMonth() - birthDate.getMonth();

  if (
    monthDiff < 0 ||
    (monthDiff === 0 && today.getDate() < birthDate.getDate())
  ) {
    age--;
  }

  return age;
}

function validateInvoiceDetails(paymentType, companyName, ico) {
  if (paymentType !== "invoice") return true;
  return (
    validateRequired(companyName) &&
    validateRequired(ico) &&
    /^[0-9]{1,20}$/.test(ico)
  );
}

function validateEquipmentOther(equipOtherChecked, equipOtherText) {
  if (!equipOtherChecked) return true;
  return validateRequired(equipOtherText);
}
