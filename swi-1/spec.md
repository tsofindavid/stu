# SOFTWARE REQUIREMENTS SPECIFICATION

# BikeFlow

## Smart Bike Sharing System

**Version 1.0**
**December 2025**

**Student Project**
**Software Engineering Course**

---

## Document Change Control

| Version | Date       | Changes Description                                  |
| ------- | ---------- | ---------------------------------------------------- |
| 1.0     | 01.12.2025 | Initial document creation with all required sections |

---

## Table of Contents

1. User Specification
   1.1. Introduction to the Problem Domain
   1.2. User Requirements
2. System Specification
   2.1. Use Case Diagram
   2.2. Use Case Tables
   2.3. Class Diagram
   2.4. Activity and Sequence Diagrams
   2.5. State Diagrams
3. Acceptance Tests
4. Project Planning
   4.1. Gantt Chart and Work Breakdown Structure
   4.2. Network Diagram

---

## Abbreviations

| Term | Definition                        |
| ---- | --------------------------------- |
| API  | Application Programming Interface |
| GPS  | Global Positioning System         |
| NFC  | Near Field Communication          |
| QR   | Quick Response (code)             |
| SMS  | Short Message Service             |

---

# 1. USER SPECIFICATION

## 1.1. Introduction to the Problem Domain

### Background

Bike sharing is a service where people can rent bicycles for short trips around the city. The system has two main users: administrators (who own the bikes) and customers (who rent them).

### How It Works

Customers register in the system through a mobile app or website. They can see available bikes on a map, rent a bike by scanning a QR code, ride to their destination, and return it to any station. The system calculates the cost based on rental time.

Administrators manage the entire system remotely. They can see all bikes, check their condition, set prices, and schedule maintenance. The system automatically alerts them when bikes need service.

### Business Rules

**Pricing:**

- Different prices for different times (weekday/weekend, day/night)
- First 30 minutes often free
- Special discounts for students or promotions

**Stations:**

- Located near metro, bus stops, universities, city center
- Each station has limited capacity for bikes

**Maintenance:**

- After 500 km: check brakes and gears
- After 1000 km: full inspection
- Monthly cleaning and chain lubrication

## 1.2. User Requirements

### Customer Goals

**G1: Easy bike access**
Customers want to quickly find and rent bikes near their location.

**G2: Clear pricing**
Customers want to know the cost before renting with no hidden fees.

**G3: Safe bikes**
Customers expect bikes in good condition and safe to ride.

### Administrator Goals

**G4: System control**
Administrators need to monitor all bikes, customers, and revenue.

**G5: Efficient maintenance**
Administrators want automated alerts when bikes need service.

### Functional Requirements

**FR-1: User Registration**
System allows customers to create accounts with email, phone, and payment method.

**FR-2: Bike Search**
System shows available bikes on a map with real-time information.

**FR-3: Rent Bike**
Customers can unlock bikes using QR code scanning or NFC.

**FR-4: Return Bike**
Customers lock bikes at any station and rental automatically ends.

**FR-5: Payment Processing**
System calculates cost and charges customer automatically.

**FR-6: Rental History**
System stores all rental records with dates, times, and costs.

**FR-7: Tariff Management**
Administrators can create and modify pricing plans.

**FR-8: Maintenance Tracking**
System tracks bike usage and generates maintenance alerts automatically.

**FR-9: Bike Monitoring**
System tracks bike location, battery level, and lock status in real-time.

**FR-10: Notifications**
System sends emails and SMS for rental confirmations and promotions.

### Non-Functional Requirements

**NFR-1: Performance**

- System handles 1,000 concurrent users
- Response time under 2 seconds for 95% of requests

**NFR-2: Availability**

- System available 99% of the time
- Maximum 3.65 days downtime per year

**NFR-3: Security**

- All data encrypted (HTTPS)
- Passwords hashed securely
- Payment data meets security standards

**NFR-4: Usability**

- New users complete registration in under 5 minutes
- Rental process requires maximum 3 clicks

**NFR-5: Compatibility**

- Mobile app works on iOS 14+ and Android 9+
- Web works on Chrome, Firefox, Safari

### Domain Requirements

**DR-1: Safety Standards**
All bikes must have working lights, brakes, and bell.

**DR-2: Age Restriction**
Users must be at least 16 years old.

**DR-3: Data Protection**
System must comply with GDPR privacy regulations.

---

# 2. SYSTEM SPECIFICATION

## 2.1. Use Case Diagram

```
                    BikeFlow System
┌───────────────────────────────────────────────────────┐
│                                                       │
│    Customer                                           │
│       │                                              │
│       │────────> (UC-1) Register Account            │
│       │────────> (UC-2) Search Bikes                │
│       │────────> (UC-3) Rent Bike                   │
│       │────────> (UC-4) Return Bike                 │
│       │────────> (UC-5) View History                │
│       │────────> (UC-6) Make Payment                │
│       │────────> (UC-7) Report Problem              │
│                                                       │
│                                                       │
│    Administrator                                      │
│       │                                              │
│       │────────> (UC-8) Monitor Bikes               │
│       │────────> (UC-9) Schedule Maintenance        │
│       │────────> (UC-10) Create Tariff              │
│       │────────> (UC-11) View Reports               │
│       │────────> (UC-12) Manage Stations            │
│       │────────> (UC-13) Send Notifications         │
│                                                       │
│                                                       │
│    Maintenance Staff                                  │
│       │                                              │
│       │────────> (UC-14) View Work Orders           │
│       │────────> (UC-15) Complete Maintenance       │
│                                                       │
│                                                       │
│    External Systems:                                  │
│    - Payment Gateway (Stripe, PayPal)                │
│    - SMS/Email Service                               │
│    - GPS System                                      │
│                                                       │
└───────────────────────────────────────────────────────┘
```

## 2.2. Use Case Tables

### Use Case 1: Rent Bike

| Field                | Description                                                                                                                                                                                                                                                                                                                                                                                               |
| -------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **ID**               | UC-3                                                                                                                                                                                                                                                                                                                                                                                                      |
| **Name**             | Rent Bike                                                                                                                                                                                                                                                                                                                                                                                                 |
| **Description**      | Customer finds an available bike, scans QR code, unlocks it, and starts rental                                                                                                                                                                                                                                                                                                                            |
| **Actors**           | Customer (primary), Payment Gateway, Bike Lock System                                                                                                                                                                                                                                                                                                                                                     |
| **Pre-conditions**   | - Customer is logged in<br>- Customer has valid payment method<br>- Bike is available                                                                                                                                                                                                                                                                                                                     |
| **Trigger**          | Customer clicks "Rent Now" button                                                                                                                                                                                                                                                                                                                                                                         |
| **Main Flow**        | 1. Customer opens app and sees map with available bikes<br>2. Customer selects a bike<br>3. System shows bike details and price<br>4. Customer confirms rental<br>5. System verifies customer account and payment<br>6. System generates QR code<br>7. Customer scans QR code on bike<br>8. Bike unlocks<br>9. System starts rental timer<br>10. System sends confirmation SMS<br>11. Customer rides bike |
| **Alternative Flow** | **A1: Bike unavailable (step 6)**<br>- System shows error "Bike already rented"<br>- System suggests other nearby bikes<br><br>**A2: Lock failure (step 8)**<br>- System retries unlock 3 times<br>- If failed, marks bike as faulty<br>- Customer not charged<br>- System suggests alternative bike                                                                                                      |
| **Post-conditions**  | - Rental record created<br>- Bike marked as "In Use"<br>- Timer started<br>- SMS sent                                                                                                                                                                                                                                                                                                                     |

---

### Use Case 2: Schedule Maintenance

| Field                | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| -------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **ID**               | UC-9                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| **Name**             | Schedule Maintenance                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| **Description**      | System detects bike needs maintenance and creates work order for staff                                                                                                                                                                                                                                                                                                                                                                                                      |
| **Actors**           | Administrator, Maintenance Staff, Automated System                                                                                                                                                                                                                                                                                                                                                                                                                          |
| **Pre-conditions**   | - Bike usage data is tracked<br>- Maintenance thresholds configured<br>- Staff accounts exist                                                                                                                                                                                                                                                                                                                                                                               |
| **Trigger**          | Bike reaches 500km or problem reported                                                                                                                                                                                                                                                                                                                                                                                                                                      |
| **Main Flow**        | 1. System checks bike odometer (501 km)<br>2. System detects threshold exceeded (500 km)<br>3. System creates maintenance alert<br>4. System marks bike as "Pending Maintenance"<br>5. System removes bike from available list<br>6. System finds available staff member<br>7. System assigns work order to staff<br>8. System sends email notification to staff<br>9. Staff receives mobile app alert<br>10. Staff accepts work order<br>11. Admin sees alert on dashboard |
| **Alternative Flow** | **A1: No staff available (step 6)**<br>- System adds to maintenance queue<br>- System schedules for next available time<br><br>**A2: Urgent repair needed**<br>- System sets priority to HIGH<br>- System immediately notifies all staff<br>- If bike is rented, customer gets return notification                                                                                                                                                                          |
| **Post-conditions**  | - Work order created<br>- Bike unavailable for rent<br>- Staff notified<br>- Dashboard updated                                                                                                                                                                                                                                                                                                                                                                              |

---

### Use Case 3: Create Tariff

| Field                | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| -------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **ID**               | UC-10                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      |
| **Name**             | Create Tariff                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| **Description**      | Administrator creates new pricing plan for specific conditions                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| **Actors**           | Administrator                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| **Pre-conditions**   | - Administrator is logged in<br>- Has tariff management permissions                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| **Trigger**          | Administrator needs new pricing strategy                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| **Main Flow**        | 1. Administrator opens Tariff Management<br>2. Administrator clicks "Create New Tariff"<br>3. Administrator enters name: "Weekend Special"<br>4. Administrator sets base fee: €1.00<br>5. Administrator sets per-minute rate: €0.10<br>6. Administrator sets free time: 30 minutes<br>7. Administrator sets valid days: Saturday, Sunday<br>8. Administrator sets valid months: June-August<br>9. Administrator sets priority: 8<br>10. Administrator saves tariff<br>11. System validates all fields<br>12. System checks for conflicts with existing tariffs<br>13. System creates tariff record<br>14. System updates pricing engine<br>15. System sends notification to subscribed customers<br>16. Administrator sees success message |
| **Alternative Flow** | **A1: Conflict detected (step 12)**<br>- System shows overlapping tariff<br>- Administrator can adjust dates or priority<br>- System explains which tariff will apply<br><br>**A2: Invalid pricing (step 11)**<br>- System shows error (e.g., daily max less than hourly rate)<br>- Administrator fixes values<br>- Validation continues                                                                                                                                                                                                                                                                                                                                                                                                   |
| **Post-conditions**  | - Tariff created and active<br>- Customers notified<br>- Pricing engine updated                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            |

## 2.3. Class Diagram

```
┌─────────────────────────┐
│        User             │
├─────────────────────────┤
│ - userId: String        │
│ - email: String         │
│ - password: String      │
│ - phoneNumber: String   │
│ - registrationDate: Date│
├─────────────────────────┤
│ + login(): Boolean      │
│ + logout(): void        │
└────────┬────────────────┘
         │
         │ inherits
         │
    ┌────┴─────┬──────────────┐
    │          │              │
┌───▼────┐ ┌───▼────────┐ ┌──▼───────────┐
│Customer│ │Administrator│ │MaintenanceStaff│
├────────┤ ├────────────┤ ├──────────────┤
│-customerId│-adminId   │ │-staffId      │
├────────┤ ├────────────┤ ├──────────────┤
│+rentBike│ │+createTariff│ │+completeMaint│
└───┬────┘ └────────────┘ └──────────────┘
    │
    │ 0..*
    │ makes
    │
┌───▼──────────────────┐
│      Rental          │
├──────────────────────┤
│ - rentalId: String   │
│ - startTime: DateTime│
│ - endTime: DateTime  │
│ - totalCost: Float   │
│ - status: String     │
├──────────────────────┤
│ + calculateCost()    │
│ + startRental()      │
│ + endRental()        │
└──────┬───────────────┘
       │
       │ 1 (uses)
       │
┌──────▼──────────────────┐
│       Bike              │
├─────────────────────────┤
│ - bikeId: String        │
│ - type: String          │
│ - status: String        │
│ - currentStationId: String│
│ - totalKilometers: Float│
│ - batteryLevel: Integer │
│ - qrCode: String        │
│ - gpsLatitude: Float    │
│ - gpsLongitude: Float   │
├─────────────────────────┤
│ + lock(): Boolean       │
│ + unlock(): Boolean     │
│ + updateLocation(): void│
└──────┬──────────────────┘
       │
       │ 1..* (located at)
       │
┌──────▼──────────────────┐
│      Station            │
├─────────────────────────┤
│ - stationId: String     │
│ - name: String          │
│ - address: String       │
│ - latitude: Float       │
│ - longitude: Float      │
│ - capacity: Integer     │
│ - availableBikes: Integer│
├─────────────────────────┤
│ + getAvailability(): Int│
│ + addBike(): void       │
│ + removeBike(): void    │
└─────────────────────────┘


┌─────────────────────────┐
│       Tariff            │
├─────────────────────────┤
│ - tariffId: String      │
│ - name: String          │
│ - baseFee: Float        │
│ - perMinuteRate: Float  │
│ - freeMinutes: Integer  │
│ - validDays: String[]   │
│ - startDate: Date       │
│ - endDate: Date         │
│ - priority: Integer     │
├─────────────────────────┤
│ + calculatePrice(): Float│
│ + isApplicable(): Boolean│
└──────┬──────────────────┘
       │
       │ 0..1 (applies to)
       │
    Rental


┌─────────────────────────┐
│   MaintenanceTask       │
├─────────────────────────┤
│ - taskId: String        │
│ - bikeId: String        │
│ - assignedStaffId: String│
│ - taskType: String      │
│ - priority: String      │
│ - scheduledDate: Date   │
│ - status: String        │
├─────────────────────────┤
│ + assignToStaff(): void │
│ + markComplete(): void  │
└──────┬──────────────────┘
       │
       │ 0..* (performed on)
       │
     Bike


┌─────────────────────────┐
│      Payment            │
├─────────────────────────┤
│ - paymentId: String     │
│ - rentalId: String      │
│ - amount: Float         │
│ - paymentMethod: String │
│ - status: String        │
│ - timestamp: DateTime   │
├─────────────────────────┤
│ + process(): Boolean    │
│ + refund(): Boolean     │
└──────┬──────────────────┘
       │
       │ 1 (pays for)
       │
    Rental

Relationships:
- Customer 1 ──< 0..* Rental
- Rental 0..* >── 1 Bike
- Bike 1..* >── 1 Station
- Tariff 0..1 ──< 0..* Rental
- MaintenanceTask 0..* >── 1 Bike
- Payment 1 ──< 1 Rental
```

## 2.4. Activity and Sequence Diagrams

### Activity Diagram 1: Rent Bike Process

```
          START
            │
            ▼
      ┌──────────┐
      │ Open App │
      └────┬─────┘
           │
           ▼
      ┌──────────┐
      │ View Map │
      │ with     │
      │ Bikes    │
      └────┬─────┘
           │
           ▼
      ┌──────────┐
      │ Select   │
      │ Bike     │
      └────┬─────┘
           │
           ▼
      ◇ Available? ◇
      │          │
   Yes│          │No
      │          │
      ▼          ▼
 ┌─────────┐  ┌─────────┐
 │ Confirm │  │ Show    │
 │ Rental  │  │ Error   │
 └────┬────┘  └────┬────┘
      │            │
      │            ▼
      │          [END]
      │
      ▼
 ┌─────────┐
 │ Verify  │
 │ Account │
 └────┬────┘
      │
      ▼
 ┌─────────┐
 │Generate │
 │QR Code  │
 └────┬────┘
      │
      ▼
 ┌─────────┐
 │ Scan QR │
 │ on Bike │
 └────┬────┘
      │
      ▼
 ◇ Lock Opens? ◇
 │           │
Yes│          │No
 │           │
 ▼           ▼
 │     ┌─────────┐
 │     │ Retry   │
 │     │ 3 times │
 │     └────┬────┘
 │          │
 │          ▼
 │     ┌─────────┐
 │     │ Mark    │
 │     │ Faulty  │
 │     └────┬────┘
 │          │
 │          ▼
 │        [END]
 │
 ▼
┌─────────┐
│ Start   │
│ Rental  │
│ Timer   │
└────┬────┘
     │
     ▼
┌─────────┐
│ Send    │
│ SMS     │
└────┬────┘
     │
     ▼
┌─────────┐
│Customer │
│ Rides   │
└────┬────┘
     │
     ▼
   [END]
```

### Activity Diagram 2: Automated Maintenance Check

```
          START
      (Hourly Cron)
            │
            ▼
      ┌──────────┐
      │ Query    │
      │ All Bikes│
      └────┬─────┘
           │
           │ For each bike
           ▼
      ┌──────────┐
      │ Check    │
      │ Odometer │
      └────┬─────┘
           │
           ▼
      ◇ >500km? ◇
      │        │
   No │        │ Yes
      │        │
      │        ▼
      │   ┌──────────┐
      │   │ Create   │
      │   │ Alert    │
      │   └────┬─────┘
      │        │
      │        ▼
      │   ┌──────────┐
      │   │ Mark Bike│
      │   │ Pending  │
      │   │ Maint.   │
      │   └────┬─────┘
      │        │
      │        ▼
      │   ┌──────────┐
      │   │ Find     │
      │   │ Available│
      │   │ Staff    │
      │   └────┬─────┘
      │        │
      │        ▼
      │   ◇ Staff? ◇
      │   │      │
      │Yes│      │No
      │   │      │
      │   ▼      ▼
      │   │  ┌──────┐
      │   │  │ Queue│
      │   │  └──┬───┘
      │   │     │
      │   └─────┘
      │        │
      │        ▼
      │   ┌──────────┐
      │   │ Assign   │
      │   │ Work     │
      │   │ Order    │
      │   └────┬─────┘
      │        │
      │        ▼
      │   ┌──────────┐
      │   │ Send     │
      │   │ Email &  │
      │   │ Notif.   │
      │   └────┬─────┘
      │        │
      └────────┘
           │
           ▼
      ┌──────────┐
      │ Continue │
      │ to Next  │
      │ Bike     │
      └────┬─────┘
           │
           ▼
      ◇ More Bikes? ◇
      │           │
   Yes│           │No
      │           │
      └───────┐   │
              │   │
              └───┘
                  │
                  ▼
                [END]
```

### Sequence Diagram 1: Rent Bike

```
Customer  Mobile App  Backend API  Database  Bike Lock  SMS Service
   │          │            │          │          │          │
   │ Open App │            │          │          │          │
   │─────────>│            │          │          │          │
   │          │ Get Bikes  │          │          │          │
   │          │───────────>│          │          │          │
   │          │            │ Query    │          │          │
   │          │            │─────────>│          │          │
   │          │            │ Return   │          │          │
   │          │            │<─────────│          │          │
   │          │ Show Map   │          │          │          │
   │          │<───────────│          │          │          │
   │          │            │          │          │          │
   │ Select   │            │          │          │          │
   │ Bike     │            │          │          │          │
   │─────────>│            │          │          │          │
   │          │ Rent Bike  │          │          │          │
   │          │───────────>│          │          │          │
   │          │            │ Verify   │          │          │
   │          │            │─────────>│          │          │
   │          │            │ OK       │          │          │
   │          │            │<─────────│          │          │
   │          │            │ Create   │          │          │
   │          │            │ Rental   │          │          │
   │          │            │─────────>│          │          │
   │          │ QR Code    │          │          │          │
   │          │<───────────│          │          │          │
   │ Scan QR  │            │          │          │          │
   │─────────>│            │          │          │          │
   │          │ Unlock     │          │          │          │
   │          │───────────>│          │          │          │
   │          │            │ Send Unlock         │          │
   │          │            │────────────────────>│          │
   │          │            │ Unlocked│          │          │
   │          │            │<────────────────────│          │
   │          │            │ Start Timer         │          │
   │          │            │─────────>│          │          │
   │          │            │ Send SMS│          │          │
   │          │            │─────────────────────────────>│
   │          │ Success    │          │          │          │
   │          │<───────────│          │          │          │
   │<─────────│            │          │          │          │
   │  Ride    │            │          │          │          │
```

### Sequence Diagram 2: Schedule Maintenance

```
System     Database    Bike    Admin      Staff     Email
  │            │        │      Dashboard   │         │
  │ Hourly     │        │          │       │         │
  │ Check      │        │          │       │         │
  │───────────>│        │          │       │         │
  │ Get Bikes  │        │          │       │         │
  │───────────>│        │          │       │         │
  │ Bike List  │        │          │       │         │
  │<───────────│        │          │       │         │
  │            │        │          │       │         │
  │ Check      │        │          │       │         │
  │ BIKE-123   │        │          │       │         │
  │ Odometer:  │        │          │       │         │
  │ 505km      │        │          │       │         │
  │──────────────────>│  │          │       │         │
  │            │        │          │       │         │
  │ Threshold  │        │          │       │         │
  │ Exceeded!  │        │          │       │         │
  │            │        │          │       │         │
  │ Create     │        │          │       │         │
  │ Work Order │        │          │       │         │
  │───────────>│        │          │       │         │
  │            │        │          │       │         │
  │ Update     │        │          │       │         │
  │ Bike Status│        │          │       │         │
  │───────────>│        │          │       │         │
  │            │        │          │       │         │
  │ Assign to  │        │          │       │         │
  │ Staff-22   │        │          │       │         │
  │───────────>│        │          │       │         │
  │            │        │          │       │         │
  │ Send Email │        │          │       │         │
  │────────────────────────────────────────────────>│
  │            │        │          │       │         │
  │            │        │          │       │ Email   │
  │            │        │          │       │ Received│
  │            │        │          │       │<────────│
  │            │        │          │       │         │
  │ Update     │        │          │       │         │
  │ Dashboard  │        │          │       │         │
  │────────────────────────────────>│      │         │
  │            │        │          │       │         │
  │            │        │  Alert   │       │         │
  │            │        │  Shown   │       │         │
  │            │        │<─────────│       │         │
```

## 2.5. State Diagrams

### State Diagram 1: Bicycle Entity

```
        [START]
           │
           ▼
    ┌─────────────┐
    │  AVAILABLE  │◄────────────┐
    │ (at station)│             │
    └──────┬──────┘             │
           │                    │
           │ Customer rents     │
           ▼                    │
    ┌─────────────┐             │
    │   IN_USE    │             │
    │ (being      │             │
    │  rented)    │             │
    └──────┬──────┘             │
           │                    │
           │ Customer returns   │
           ├────────────────────┘
           │
           │ Maintenance needed
           ▼
    ┌─────────────┐
    │  PENDING_   │
    │ MAINTENANCE │
    └──────┬──────┘
           │
           │ Staff accepts
           ▼
    ┌─────────────┐
    │   UNDER_    │
    │ MAINTENANCE │
    └──────┬──────┘
           │
           ├──> Completed & OK
           │         │
           │         └──> Back to AVAILABLE
           │
           │ Major problem found
           ▼
    ┌─────────────┐
    │    OUT_OF_  │
    │   SERVICE   │
    └──────┬──────┘
           │
           │ Repaired
           └──> Back to AVAILABLE

State Descriptions:
- AVAILABLE: Ready to rent, at station
- IN_USE: Currently rented by customer
- PENDING_MAINTENANCE: Needs service, work order created
- UNDER_MAINTENANCE: Staff working on bike
- OUT_OF_SERVICE: Serious problem, cannot be used
```

### State Diagram 2: Rental Entity

```
        [START]
           │
           ▼
    ┌─────────────┐
    │  INITIATED  │
    │ (customer   │
    │  selected   │
    │   bike)     │
    └──────┬──────┘
           │
           │ Account verified
           ▼
    ┌─────────────┐
    │ AUTHORIZED  │
    │ (ready to   │
    │  unlock)    │
    └──────┬──────┘
           │
           │ QR code generated
           ▼
    ┌─────────────┐
    │  PENDING_   │
    │   UNLOCK    │
    └──────┬──────┘
           │
           ├──> Lock opens
           │         │
           │         ▼
           │  ┌─────────────┐
           │  │   ACTIVE    │◄──────────┐
           │  │  (rental    │           │
           │  │  in progress)│          │
           │  └──────┬──────┘           │
           │         │                  │
           │         │ Customer returns │
           │         ▼                  │
           │  ┌─────────────┐           │
           │  │   ENDING    │           │
           │  │ (locking    │           │
           │  │  bike)      │           │
           │  └──────┬──────┘           │
           │         │                  │
           │         │ Payment          │
           │         ▼                  │
           │  ┌─────────────┐           │
           │  │ PROCESSING_ │           │
           │  │  PAYMENT    │           │
           │  └──────┬──────┘           │
           │         │                  │
           │         ├──> Success       │
           │         │       │          │
           │         │       ▼          │
           │         │  ┌─────────────┐ │
           │         │  │ COMPLETED   │ │
           │         │  └─────────────┘ │
           │         │                  │
           │         │ Payment failed   │
           │         ▼                  │
           │  ┌─────────────┐           │
           │  │  PAYMENT_   │           │
           │  │   FAILED    │           │
           │  └──────┬──────┘           │
           │         │                  │
           │         │ Retry            │
           │         └──────────────────┘
           │
           │ Lock fails
           ▼
    ┌─────────────┐
    │   FAILED    │
    │ (rental not │
    │  started)   │
    └──────┬──────┘
           │
           │ Refund processed
           ▼
    ┌─────────────┐
    │  CANCELLED  │
    └─────────────┘
           │
           ▼
        [END]

State Descriptions:
- INITIATED: Customer started rental process
- AUTHORIZED: Account and payment verified
- PENDING_UNLOCK: Waiting for customer to scan QR
- ACTIVE: Rental in progress, timer running
- ENDING: Customer returned bike, processing return
- PROCESSING_PAYMENT: Calculating and charging cost
- COMPLETED: Rental finished successfully
- PAYMENT_FAILED: Payment unsuccessful, will retry
- FAILED: Rental could not start (lock problem)
- CANCELLED: Rental terminated, refund issued
```

---

# 3. ACCEPTANCE TESTS

## Test 1: Complete Rental (Functional)

| Field               | Content                                                                                                      |
| ------------------- | ------------------------------------------------------------------------------------------------------------ |
| **ID**              | AT-F-01                                                                                                      |
| **Use Case**        | UC-3 (Rent Bike)                                                                                             |
| **Objective**       | Verify customer can rent and return bike successfully                                                        |
| **Pre-conditions**  | - Customer account exists (CUST-100)<br>- Credit card on file<br>- Bike BIKE-50 available at Central Station |
| **Post-conditions** | - Rental completed<br>- Payment €3.50 processed<br>- Bike available again                                    |

| Step | Action                           | Expected Result                                |
| ---- | -------------------------------- | ---------------------------------------------- |
| 1    | Customer opens app               | Map shows with nearby bikes                    |
| 2    | Customer selects BIKE-50         | Details shown: €1 base + €0.10/min             |
| 3    | Customer taps "Rent Now"         | QR code displayed                              |
| 4    | Customer scans QR on bike        | Bike unlocks, timer starts                     |
| 5    | Customer rides 35 minutes        | GPS tracks location                            |
| 6    | Customer returns to Park Station | App shows available spaces                     |
| 7    | Customer locks bike              | Lock confirmed, timer stops                    |
| 8    | System calculates cost           | Shows: €1 base + €0.50 (5 min × €0.10) = €1.50 |
| 9    | System processes payment         | Payment successful, receipt sent               |

## Test 2: Maintenance Scheduling (Functional)

| Field               | Content                                                                                |
| ------------------- | -------------------------------------------------------------------------------------- |
| **ID**              | AT-F-02                                                                                |
| **Use Case**        | UC-9 (Schedule Maintenance)                                                            |
| **Objective**       | Verify system automatically schedules maintenance                                      |
| **Pre-conditions**  | - BIKE-200 has 498 km<br>- Maintenance at 500 km threshold<br>- Staff member available |
| **Post-conditions** | - Work order created<br>- Bike unavailable<br>- Staff notified                         |

| Step | Action                              | Expected Result                           |
| ---- | ----------------------------------- | ----------------------------------------- |
| 1    | Customer rents BIKE-200, rides 3 km | Odometer: 498 → 501 km                    |
| 2    | System runs hourly check            | Detects 501 km > 500 km threshold         |
| 3    | System creates alert                | Alert: "500km service required"           |
| 4    | System marks bike status            | Status changed to "PENDING_MAINTENANCE"   |
| 5    | System creates work order           | WO-100 created for BIKE-200               |
| 6    | System assigns to staff             | Staff-10 assigned                         |
| 7    | System sends email                  | Email received by staff                   |
| 8    | Customer tries to rent BIKE-200     | Error: "Bike unavailable for maintenance" |

## Test 3: Create Tariff (Functional)

| Field               | Content                                                           |
| ------------------- | ----------------------------------------------------------------- |
| **ID**              | AT-F-03                                                           |
| **Use Case**        | UC-10 (Create Tariff)                                             |
| **Objective**       | Verify admin can create new pricing plan                          |
| **Pre-conditions**  | - Admin logged in<br>- Existing tariff: "Standard" (€0.15/min)    |
| **Post-conditions** | - New tariff created<br>- Customers notified<br>- Pricing updated |

| Step | Action                                                               | Expected Result                             |
| ---- | -------------------------------------------------------------------- | ------------------------------------------- |
| 1    | Admin opens Tariff Management                                        | List of current tariffs shown               |
| 2    | Admin clicks "Create New"                                            | Form displayed                              |
| 3    | Admin enters: "Student Discount", €0.50 base, €0.08/min, 30 min free | Fields validated                            |
| 4    | Admin sets: Weekdays only, Priority 7                                | Configuration accepted                      |
| 5    | Admin clicks "Save"                                                  | System validates fields                     |
| 6    | System checks conflicts                                              | No conflicts found                          |
| 7    | System creates tariff                                                | Tariff ID: TRF-2025-15                      |
| 8    | System updates pricing engine                                        | New rules cached                            |
| 9    | System sends notifications                                           | 500 student customers emailed               |
| 10   | Student rents bike on Monday                                         | Student tariff applied, €0.08/min rate used |

## Test 4: System Performance (Non-Functional)

| Field               | Content                                                                    |
| ------------------- | -------------------------------------------------------------------------- |
| **ID**              | AT-NF-01                                                                   |
| **Requirement**     | NFR-1 (Performance)                                                        |
| **Objective**       | Verify system handles 1,000 concurrent users                               |
| **Pre-conditions**  | - Test environment ready<br>- 5,000 test accounts<br>- 500 bikes available |
| **Post-conditions** | - All requests successful<br>- Response time < 2 seconds<br>- No errors    |

| Step | Action                                 | Expected Result                           |
| ---- | -------------------------------------- | ----------------------------------------- |
| 1    | Start with 100 users baseline          | Avg response: 0.3 seconds                 |
| 2    | Increase to 500 concurrent users       | Avg response: 0.8 seconds, Success: 100%  |
| 3    | Increase to 1,000 concurrent users     | Avg response: 1.5 seconds (< 2 sec ✓)     |
| 4    | Test 1,000 simultaneous "Search Bikes" | Response: 1.2 seconds avg, Success: 99.8% |
| 5    | Test 200 simultaneous rentals          | All bikes unlock successfully             |
| 6    | Test 200 simultaneous payments         | All payments process within 2 seconds     |
| 7    | Monitor for 30 minutes                 | System stable, no crashes                 |
| 8    | Check error logs                       | Only 0.2% failed (retried successfully)   |

---

# 4. PROJECT PLANNING

## 4.1. Gantt Chart and Work Breakdown Structure

### Team (4 members minimum)

1. **Alex Chen** - Backend Developer & Project Lead
2. **Maria Garcia** - Frontend/Mobile Developer
3. **David Kim** - Mobile Developer
4. **Sarah Johnson** - QA Engineer & DevOps

### Work Breakdown Structure (10+ tasks)

```
BikeFlow Project (12 weeks)
│
├── 1. Planning & Design (2 weeks)
│   ├── 1.1 Requirements Analysis
│   ├── 1.2 System Architecture
│   └── 1.3 UI/UX Design
│
├── 2. Backend Development (4 weeks)
│   ├── 2.1 Database Setup
│   ├── 2.2 User & Auth API
│   ├── 2.3 Bike & Rental API
│   └── 2.4 Payment Integration
│
├── 3. Mobile App (4 weeks)
│   ├── 3.1 iOS App Development
│   ├── 3.2 Android App Development
│   └── 3.3 QR/GPS Integration
│
├── 4. Testing (2 weeks)
│   ├── 4.1 Unit & Integration Tests
│   └── 4.2 User Acceptance Testing
│
└── 5. Deployment (1 week)
    ├── 5.1 Production Setup
    └── 5.2 Launch
```

### Gantt Chart

```
Task                    | Owner    | Duration | Week 1-12
========================|==========|==========|=====================================
1.1 Requirements        | Alex     | 1 week   | ██
1.2 Architecture        | Alex     | 1 week   |   ██
1.3 UI Design           | Maria    | 2 weeks  | ████
2.1 Database            | Alex     | 1 week   |     ██
2.2 User API            | Alex     | 2 weeks  |       ████
2.3 Bike API            | Alex     | 2 weeks  |           ████
2.4 Payment             | Alex     | 1 week   |               ██
3.1 iOS App             | Maria    | 3 weeks  |       ██████
3.2 Android App         | David    | 3 weeks  |       ██████
3.3 QR/GPS              | David    | 1 week   |             ██
4.1 Testing             | Sarah    | 2 weeks  |               ████
4.2 UAT                 | Sarah    | 1 week   |                   ██
5.1 Deployment          | Sarah    | 1 week   |                     ██
5.2 Launch              | All      | 1 day    |                       █
```

### Task Dependencies

| Task             | Depends On | Duration |
| ---------------- | ---------- | -------- |
| 1.1 Requirements | -          | 1 week   |
| 1.2 Architecture | 1.1        | 1 week   |
| 1.3 UI Design    | 1.1        | 2 weeks  |
| 2.1 Database     | 1.2        | 1 week   |
| 2.2 User API     | 2.1        | 2 weeks  |
| 2.3 Bike API     | 2.1        | 2 weeks  |
| 2.4 Payment      | 2.2        | 1 week   |
| 3.1 iOS App      | 1.3, 2.2   | 3 weeks  |
| 3.2 Android App  | 1.3, 2.2   | 3 weeks  |
| 3.3 QR/GPS       | 3.1, 3.2   | 1 week   |
| 4.1 Testing      | 2.4, 3.3   | 2 weeks  |
| 4.2 UAT          | 4.1        | 1 week   |
| 5.1 Deployment   | 4.2        | 1 week   |
| 5.2 Launch       | 5.1        | 1 day    |

### Milestones

| Milestone | Date    | Deliverable        |
| --------- | ------- | ------------------ |
| M1        | Week 2  | Design Complete    |
| M2        | Week 6  | Backend APIs Ready |
| M3        | Week 8  | Mobile Apps Beta   |
| M4        | Week 10 | Testing Complete   |
| M5        | Week 12 | Production Launch  |

## 4.2. Network Diagram (Critical Path Method)

```
                START
                  │
                  ▼
          ┌───────────────┐
          │ 1.1 Require.  │
          │   (1 week)    │
          │   [Alex]      │
          └───────┬───────┘
                  │
        ┌─────────┼─────────┐
        │         │         │
        ▼         ▼         ▼
    ┌───────┐ ┌───────┐ ┌───────┐
    │ 1.2   │ │ 1.3   │ │       │
    │ Arch. │ │ Design│ │       │
    │1 week │ │2 weeks│ │       │
    │[Alex] │ │[Maria]│ │       │
    └───┬───┘ └───┬───┘ │       │
        │         │     │       │
        ▼         │     │       │
    ┌───────┐     │     │       │
    │ 2.1   │     │     │       │
    │ DB    │     │     │       │
    │1 week │     │     │       │
    │[Alex] │     │     │       │
    └───┬───┘     │     │       │
        │         │     │       │
        ▼         │     │       │
    ┌───────┐     │     │       │
    │ 2.2   │     │     │       │
    │UserAPI│◄────┘     │       │
    │2 weeks│           │       │
    │[Alex] │           │       │
    └───┬───┘           │       │
        │               │       │
    ┌───┼───────────────┘       │
    │   │                       │
    ▼   ▼                       ▼
┌───────┐ ┌───────┐         ┌───────┐
│ 2.3   │ │ 3.1   │         │ 3.2   │
│BikeAPI│ │ iOS   │         │Android│
│2 weeks│ │3 weeks│         │3 weeks│
│[Alex] │ │[Maria]│         │[David]│
└───┬───┘ └───┬───┘         └───┬───┘
    │         │                 │
    ▼         │                 │
┌───────┐     └────────┬────────┘
│ 2.4   │              │
│Payment│              ▼
│1 week │         ┌───────┐
│[Alex] │         │ 3.3   │
└───┬───┘         │QR/GPS │
    │             │1 week │
    │             │[David]│
    │             └───┬───┘
    │                 │
    └────────┬────────┘
             │
             ▼
        ┌───────┐
        │ 4.1   │
        │Testing│
        │2 weeks│
        │[Sarah]│
        └───┬───┘
            │
            ▼
        ┌───────┐
        │ 4.2   │
        │  UAT  │
        │1 week │
        │[Sarah]│
        └───┬───┘
            │
            ▼
        ┌───────┐
        │ 5.1   │
        │Deploy │
        │1 week │
        │[Sarah]│
        └───┬───┘
            │
            ▼
        ┌───────┐
        │ 5.2   │
        │Launch │
        │1 day  │
        │ [All] │
        └───┬───┘
            │
            ▼
          END
```

### Critical Path

**Critical Path (longest path):**
1.1 → 1.2 → 2.1 → 2.2 → 3.1 → 4.1 → 4.2 → 5.1 → 5.2

**Total Duration: 12 weeks**

**Activities on Critical Path:**

- 1.1 Requirements (1 week)
- 1.2 Architecture (1 week)
- 2.1 Database (1 week)
- 2.2 User API (2 weeks)
- 3.1 iOS App (3 weeks)
- 4.1 Testing (2 weeks)
- 4.2 UAT (1 week)
- 5.1 Deployment (1 week)
- 5.2 Launch (1 day)

**Critical Path Duration: 12 weeks + 1 day**

Any delay in these tasks will delay the entire project!

### Resource Loading

| Week | Alex                       | Maria              | David           | Sarah      |
| ---- | -------------------------- | ------------------ | --------------- | ---------- |
| 1-2  | Requirements, Architecture | UI Design          | -               | -          |
| 3-4  | Database, User API         | UI Design, iOS App | -               | -          |
| 5-6  | Bike API                   | iOS App            | Android App     | -          |
| 7-8  | Payment                    | iOS App            | Android, QR/GPS | -          |
| 9-10 | Support                    | Support            | Support         | Testing    |
| 11   | Support                    | Support            | Support         | UAT        |
| 12   | Deploy Support             | Deploy Support     | Deploy Support  | Deployment |

---

**END OF DOCUMENT**

---

## Notes for Examination/Defense

**Key Points to Remember:**

1. **BikeFlow** - Simple, memorable name for student project
2. **15 Use Cases** - Covers all main functionality (Customer: 7, Admin: 6, Staff: 2)
3. **8 Classes** - Core entities with proper relationships
4. **Critical Path**: 12 weeks - Be ready to explain why these tasks are critical
5. **Team**: 4 people (minimum requirement met)
6. **State Diagrams**: Both Bicycle and Rental as required

**Expected Questions:**

- "Why did you choose these use cases?" → Most important for basic functionality
- "Why 12 weeks?" → Realistic for student project with 4 people
- "What if task X is delayed?" → Show critical path understanding
- "Why these non-functional requirements?" → Industry standard for small system

**Simplifications Made (vs. Real Project):**

- Fewer use cases (15 vs 30+)
- Simplified class diagram (8 classes vs 15+)
- Shorter timeline (12 weeks vs 20 weeks)
- Smaller team (4 vs 11 people)
- Basic acceptance tests (4 vs many more)

This is appropriate for a **student examination project**. ✓
