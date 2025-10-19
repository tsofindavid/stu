//   const birthDateField = document.getElementById("birthDate");
//   const ageField = document.getElementById("age");
//   const ageError = document.getElementById("ageError");

export class ValidateError extends Error {
  errors;

  constructor(errors = []) {
    this.errors = errors;
  }
}

export function validateAge(age) {
  //   if (!birthDateField.value || !ageField.value) return false;
  //   const birthDate = new Date(birthDateField.value);
  //   const today = new Date();
  //   let calculatedAge = today.getFullYear() - birthDate.getFullYear();
  //   const monthDiff = today.getMonth() - birthDate.getMonth();
  //   if (
  //     monthDiff < 0 ||
  //     (monthDiff === 0 && today.getDate() < birthDate.getDate())
  //   ) {
  //     calculatedAge--;
  //   }
  //   if (parseInt(ageField.value) !== calculatedAge) {
  //     ageError.textContent = "Vek nezodpovedá dátumu narodenia";
  //     ageField.classList.add("error");
  //     return false;
  //   } else {
  //     ageError.textContent = "";
  //     ageField.classList.remove("error");
  //     return true;
  //   }
}

// RFC 5322
export function validateEmail(email) {
  const emailRegex =
    /^[a-zA-Z0-9]([a-zA-Z0-9._-]{1,})?[a-zA-Z0-9]@([a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,4}$/;

  if (!emailRegex.test(email)) {
    return false;
  }

  const [localPart, domain] = email.split("@");

  if (localPart.length < 3) {
    return false;
  }

  if (email.includes("..")) {
    return false;
  }

  const domainParts = domain.split(".");
  if (domainParts.length < 2) {
    return false;
  }

  const topLevelDomain = domainParts[domainParts.length - 1];
  if (topLevelDomain.length < 2 || topLevelDomain.length > 4) {
    return false;
  }

  return true;
}

export function validatePhone(phone) {
  const cleanPhone = phone.replace(/[\s\-\(\)]/g, "");
  const phoneRegex = /^[0-9]{9,15}$/;

  return phoneRegex.test(cleanPhone);
}
