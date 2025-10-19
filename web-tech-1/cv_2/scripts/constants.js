export const sportData = {
  football: {
    facilities: {
      outdoor: { name: "Vonkajšie ihrisko", price: 20 },
      indoor: { name: "Vnútorná hala", price: 35 },
    },
  },
  tennis: {
    facilities: {
      court1: { name: "Kurt 1", price: 25 },
      court2: { name: "Kurt 2", price: 30 },
    },
  },
  basketball: {
    facilities: {
      gym1: { name: "Telocvičňa 1", price: 30 },
      gym2: { name: "Telocvičňa 2", price: 35 },
    },
  },
  volleyball: {
    facilities: {
      beach: { name: "Plážové ihrisko", price: 15 },
      indoor: { name: "Vnútorná hala", price: 30 },
    },
  },
};

export const timeSlots = {
  outdoor: [
    { value: "08:00", label: "08:00 - 10:00", price: 0 },
    { value: "10:00", label: "10:00 - 12:00", price: 5 },
    { value: "12:00", label: "12:00 - 14:00", price: 10 },
  ],
  indoor: [
    { value: "14:00", label: "14:00 - 16:00", price: 0 },
    { value: "16:00", label: "16:00 - 18:00", price: 5 },
    { value: "18:00", label: "18:00 - 20:00", price: 10 },
  ],
  court1: [
    { value: "06:00", label: "06:00 - 08:00", price: 0 },
    { value: "08:00", label: "08:00 - 10:00", price: 5 },
  ],
  court2: [
    { value: "10:00", label: "10:00 - 12:00", price: 0 },
    { value: "12:00", label: "12:00 - 14:00", price: 5 },
  ],
  gym1: [
    { value: "07:00", label: "07:00 - 09:00", price: 0 },
    { value: "09:00", label: "09:00 - 11:00", price: 5 },
  ],
  gym2: [
    { value: "11:00", label: "11:00 - 13:00", price: 0 },
    { value: "13:00", label: "13:00 - 15:00", price: 5 },
  ],
  beach: [
    { value: "08:00", label: "08:00 - 10:00", price: 0 },
    { value: "10:00", label: "10:00 - 12:00", price: 5 },
  ],
};
