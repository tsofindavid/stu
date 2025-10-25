let store = Object.values(FIELD_IDS).reduce(
  (obj, field) => ({ ...obj, [field]: undefined }),
  {},
);

function initStore() {
  store = Object.values(FIELD_IDS).reduce(
    (obj, field) => ({
      ...obj,
      [field]: document.getElementById(field),
    }),
    {},
  );
}
