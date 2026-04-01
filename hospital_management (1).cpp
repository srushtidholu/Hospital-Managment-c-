/*
============================================================
   HOSPITAL MANAGEMENT SYSTEM
   Subject: Object-Oriented Programming using C++
   Language: C++
   OOP Concepts Demonstrated:
     1. Encapsulation
     2. Inheritance
     3. Polymorphism
     4. Abstraction
============================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <algorithm>
using namespace std;

// ============================================================
// ABSTRACTION: Abstract Base Class - Person
// Defines a pure virtual interface for all persons in the system
// ============================================================
class Person {
protected:
    int    id;
    string name;
    int    age;
    string gender;
    string phone;

public:
    Person(int id, const string& name, int age,
           const string& gender, const string& phone)
        : id(id), name(name), age(age),
          gender(gender), phone(phone) {}

    // Pure virtual functions => Abstract class
    virtual void displayInfo()    const = 0;
    virtual string getRole()      const = 0;

    // Getters (Encapsulation)
    int    getId()     const { return id; }
    string getName()   const { return name; }
    int    getAge()    const { return age; }
    string getGender() const { return gender; }
    string getPhone()  const { return phone; }

    virtual ~Person() {}
};

// ============================================================
// INHERITANCE + ENCAPSULATION: Doctor class
// ============================================================
class Doctor : public Person {
private:
    string specialization;
    string availability;   // e.g., "Mon-Fri 9AM-5PM"
    double consultationFee;

public:
    Doctor(int id, const string& name, int age,
           const string& gender, const string& phone,
           const string& spec, const string& avail,
           double fee)
        : Person(id, name, age, gender, phone),
          specialization(spec),
          availability(avail),
          consultationFee(fee) {}

    // POLYMORPHISM: Override displayInfo()
    void displayInfo() const override {
        cout << left
             << setw(6)  << id
             << setw(20) << name
             << setw(5)  << age
             << setw(8)  << gender
             << setw(20) << specialization
             << setw(22) << availability
             << "Rs. " << fixed << setprecision(2) << consultationFee
             << "\n";
    }

    string getRole()           const override { return "Doctor"; }
    string getSpecialization() const { return specialization; }
    double getFee()            const { return consultationFee; }
};

// ============================================================
// INHERITANCE + ENCAPSULATION: Patient class
// ============================================================
class Patient : public Person {
private:
    string bloodGroup;
    string disease;
    string admitDate;
    bool   isAdmitted;
    int    assignedDoctorId;

public:
    Patient(int id, const string& name, int age,
            const string& gender, const string& phone,
            const string& blood, const string& disease,
            const string& date, bool admitted = false,
            int docId = -1)
        : Person(id, name, age, gender, phone),
          bloodGroup(blood), disease(disease),
          admitDate(date), isAdmitted(admitted),
          assignedDoctorId(docId) {}

    // POLYMORPHISM: Override displayInfo()
    void displayInfo() const override {
        cout << left
             << setw(6)  << id
             << setw(20) << name
             << setw(5)  << age
             << setw(8)  << gender
             << setw(8)  << bloodGroup
             << setw(22) << disease
             << setw(12) << admitDate
             << setw(10) << (isAdmitted ? "Admitted" : "Out-Patient")
             << (assignedDoctorId != -1
                 ? "Dr.ID:" + to_string(assignedDoctorId)
                 : "Not Assigned")
             << "\n";
    }

    string getRole()     const override { return "Patient"; }
    string getDisease()  const { return disease; }
    string getBlood()    const { return bloodGroup; }
    bool   admitted()    const { return isAdmitted; }
    int    getDoctorId() const { return assignedDoctorId; }

    void assignDoctor(int docId)   { assignedDoctorId = docId; }
    void setAdmitted(bool status)  { isAdmitted = status; }
};

// ============================================================
// INHERITANCE + ENCAPSULATION: Staff class
// ============================================================
class Staff : public Person {
private:
    string department;
    string role;
    double salary;

public:
    Staff(int id, const string& name, int age,
          const string& gender, const string& phone,
          const string& dept, const string& role,
          double salary)
        : Person(id, name, age, gender, phone),
          department(dept), role(role), salary(salary) {}

    // POLYMORPHISM: Override displayInfo()
    void displayInfo() const override {
        cout << left
             << setw(6)  << id
             << setw(20) << name
             << setw(5)  << age
             << setw(8)  << gender
             << setw(20) << department
             << setw(20) << role
             << "Rs. " << fixed << setprecision(2) << salary
             << "\n";
    }

    string getRole() const override { return role; }
    string getDept() const { return department; }
};

// ============================================================
// ENCAPSULATION: Appointment class
// ============================================================
class Appointment {
private:
    int    appointmentId;
    int    patientId;
    int    doctorId;
    string date;
    string time;
    string status;   // Scheduled / Completed / Cancelled
    string notes;

public:
    Appointment(int aId, int pId, int dId,
                const string& date, const string& time,
                const string& notes = "")
        : appointmentId(aId), patientId(pId),
          doctorId(dId), date(date), time(time),
          status("Scheduled"), notes(notes) {}

    void display() const {
        cout << left
             << setw(6)  << appointmentId
             << setw(12) << patientId
             << setw(10) << doctorId
             << setw(14) << date
             << setw(10) << time
             << setw(14) << status
             << notes << "\n";
    }

    int    getAptId()     const { return appointmentId; }
    int    getPatientId() const { return patientId; }
    int    getDoctorId()  const { return doctorId; }
    string getStatus()    const { return status; }
    void   setStatus(const string& s) { status = s; }
};

// ============================================================
// ENCAPSULATION: Bill class
// ============================================================
class Bill {
private:
    int    billId;
    int    patientId;
    double consultationCharge;
    double medicineCharge;
    double roomCharge;
    double totalAmount;
    bool   isPaid;

public:
    Bill(int bId, int pId,
         double consult, double medicine, double room)
        : billId(bId), patientId(pId),
          consultationCharge(consult),
          medicineCharge(medicine),
          roomCharge(room),
          totalAmount(consult + medicine + room),
          isPaid(false) {}

    void display() const {
        cout << "\n";
        cout << "  ╔══════════════════════════════════════╗\n";
        cout << "  ║         HOSPITAL BILL RECEIPT        ║\n";
        cout << "  ╠══════════════════════════════════════╣\n";
        cout << "  ║  Bill ID      : " << left << setw(22) << billId       << "║\n";
        cout << "  ║  Patient ID   : " << left << setw(22) << patientId    << "║\n";
        cout << "  ╠══════════════════════════════════════╣\n";
        cout << "  ║  Consultation : Rs. " << left << setw(18)
             << fixed << setprecision(2) << consultationCharge << "║\n";
        cout << "  ║  Medicine     : Rs. " << left << setw(18)
             << fixed << setprecision(2) << medicineCharge     << "║\n";
        cout << "  ║  Room Charges : Rs. " << left << setw(18)
             << fixed << setprecision(2) << roomCharge         << "║\n";
        cout << "  ╠══════════════════════════════════════╣\n";
        cout << "  ║  TOTAL        : Rs. " << left << setw(18)
             << fixed << setprecision(2) << totalAmount        << "║\n";
        cout << "  ║  Status       : " << left << setw(22)
             << (isPaid ? "PAID" : "PENDING")                  << "║\n";
        cout << "  ╚══════════════════════════════════════╝\n\n";
    }

    void markPaid() { isPaid = true; }
    bool paid()     const { return isPaid; }
    int  getBillId()    const { return billId; }
    int  getPatientId() const { return patientId; }
};

// ============================================================
// ENCAPSULATION: HospitalManagementSystem (main controller)
// ============================================================
class HospitalManagementSystem {
private:
    string             hospitalName;
    vector<Doctor*>    doctors;
    vector<Patient*>   patients;
    vector<Staff*>     staffList;
    vector<Appointment> appointments;
    vector<Bill>       bills;

    int nextDoctorId      = 101;
    int nextPatientId     = 201;
    int nextStaffId       = 301;
    int nextAppointmentId = 401;
    int nextBillId        = 501;

    // ── Helpers ──────────────────────────────────────────────
    void printHeader(const string& title) const {
        int w = 70;
        cout << "\n" << string(w, '=') << "\n";
        int pad = (w - (int)title.size()) / 2;
        cout << string(pad, ' ') << title << "\n";
        cout << string(w, '=') << "\n";
    }

    void pause() const {
        cout << "\n  Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    Doctor* findDoctor(int id) const {
        for (auto d : doctors)
            if (d->getId() == id) return d;
        return nullptr;
    }

    Patient* findPatient(int id) const {
        for (auto p : patients)
            if (p->getId() == id) return p;
        return nullptr;
    }

public:
    HospitalManagementSystem(const string& name)
        : hospitalName(name) {}

    ~HospitalManagementSystem() {
        for (auto d : doctors)  delete d;
        for (auto p : patients) delete p;
        for (auto s : staffList) delete s;
    }

    // ── DOCTOR MANAGEMENT ────────────────────────────────────
    void addDoctor() {
        printHeader("ADD NEW DOCTOR");
        string name, gender, phone, spec, avail;
        int age; double fee;

        cout << "  Name           : "; cin.ignore(); getline(cin, name);
        cout << "  Age            : "; cin >> age;
        cout << "  Gender (M/F)   : "; cin >> gender;
        cout << "  Phone          : "; cin >> phone;
        cout << "  Specialization : "; cin.ignore(); getline(cin, spec);
        cout << "  Availability   : "; getline(cin, avail);
        cout << "  Consultation Fee (Rs.): "; cin >> fee;

        doctors.push_back(new Doctor(nextDoctorId++, name, age,
                                     gender, phone, spec, avail, fee));
        cout << "\n  ✔ Doctor added successfully! ID: "
             << nextDoctorId - 1 << "\n";
        pause();
    }

    void viewDoctors() const {
        printHeader("ALL DOCTORS");
        if (doctors.empty()) { cout << "  No doctors registered.\n"; pause(); return; }
        cout << left
             << setw(6)  << "ID"
             << setw(20) << "Name"
             << setw(5)  << "Age"
             << setw(8)  << "Gender"
             << setw(20) << "Specialization"
             << setw(22) << "Availability"
             << "Fee\n"
             << string(100, '-') << "\n";
        // POLYMORPHISM: calling overridden displayInfo()
        for (auto d : doctors) d->displayInfo();
        pause();
    }

    // ── PATIENT MANAGEMENT ───────────────────────────────────
    void addPatient() {
        printHeader("REGISTER NEW PATIENT");
        string name, gender, phone, blood, disease, date;
        int age; char admit; bool isAdmitted = false; int docId = -1;

        cout << "  Name        : "; cin.ignore(); getline(cin, name);
        cout << "  Age         : "; cin >> age;
        cout << "  Gender      : "; cin >> gender;
        cout << "  Phone       : "; cin >> phone;
        cout << "  Blood Group : "; cin >> blood;
        cout << "  Disease     : "; cin.ignore(); getline(cin, disease);
        cout << "  Admit Date  : "; getline(cin, date);
        cout << "  Admitted? (y/n): "; cin >> admit;
        isAdmitted = (admit == 'y' || admit == 'Y');

        if (!doctors.empty()) {
            cout << "  Assign Doctor ID (-1 to skip): "; cin >> docId;
        }

        patients.push_back(new Patient(nextPatientId++, name, age,
                                       gender, phone, blood, disease,
                                       date, isAdmitted, docId));
        cout << "\n  ✔ Patient registered! ID: " << nextPatientId - 1 << "\n";
        pause();
    }

    void viewPatients() const {
        printHeader("ALL PATIENTS");
        if (patients.empty()) { cout << "  No patients registered.\n"; pause(); return; }
        cout << left
             << setw(6)  << "ID"
             << setw(20) << "Name"
             << setw(5)  << "Age"
             << setw(8)  << "Gender"
             << setw(8)  << "Blood"
             << setw(22) << "Disease"
             << setw(12) << "Admit Date"
             << setw(10) << "Status"
             << "Doctor\n"
             << string(110, '-') << "\n";
        // POLYMORPHISM: calling overridden displayInfo()
        for (auto p : patients) p->displayInfo();
        pause();
    }

    void searchPatient() const {
        printHeader("SEARCH PATIENT");
        int id;
        cout << "  Enter Patient ID: "; cin >> id;
        Patient* p = findPatient(id);
        if (!p) { cout << "  Patient not found!\n"; }
        else {
            cout << "\n  Patient Details:\n  " << string(50, '-') << "\n";
            cout << "  ID      : " << p->getId()     << "\n"
                 << "  Name    : " << p->getName()   << "\n"
                 << "  Age     : " << p->getAge()    << "\n"
                 << "  Gender  : " << p->getGender() << "\n"
                 << "  Phone   : " << p->getPhone()  << "\n"
                 << "  Blood   : " << p->getBlood()  << "\n"
                 << "  Disease : " << p->getDisease()<< "\n"
                 << "  Status  : " << (p->admitted() ? "Admitted" : "Out-Patient") << "\n";
            if (p->getDoctorId() != -1) {
                Doctor* d = findDoctor(p->getDoctorId());
                if (d) cout << "  Doctor  : " << d->getName()
                            << " (" << d->getSpecialization() << ")\n";
            }
        }
        pause();
    }

    // ── STAFF MANAGEMENT ─────────────────────────────────────
    void addStaff() {
        printHeader("ADD NEW STAFF");
        string name, gender, phone, dept, role;
        int age; double salary;

        cout << "  Name       : "; cin.ignore(); getline(cin, name);
        cout << "  Age        : "; cin >> age;
        cout << "  Gender     : "; cin >> gender;
        cout << "  Phone      : "; cin >> phone;
        cout << "  Department : "; cin.ignore(); getline(cin, dept);
        cout << "  Role       : "; getline(cin, role);
        cout << "  Salary (Rs.): "; cin >> salary;

        staffList.push_back(new Staff(nextStaffId++, name, age,
                                      gender, phone, dept, role, salary));
        cout << "\n  ✔ Staff added! ID: " << nextStaffId - 1 << "\n";
        pause();
    }

    void viewStaff() const {
        printHeader("ALL STAFF MEMBERS");
        if (staffList.empty()) { cout << "  No staff registered.\n"; pause(); return; }
        cout << left
             << setw(6)  << "ID"
             << setw(20) << "Name"
             << setw(5)  << "Age"
             << setw(8)  << "Gender"
             << setw(20) << "Department"
             << setw(20) << "Role"
             << "Salary\n"
             << string(100, '-') << "\n";
        // POLYMORPHISM: calling overridden displayInfo()
        for (auto s : staffList) s->displayInfo();
        pause();
    }

    // ── APPOINTMENT MANAGEMENT ───────────────────────────────
    void bookAppointment() {
        printHeader("BOOK APPOINTMENT");
        int pId, dId;
        string date, time, notes;

        cout << "  Patient ID : "; cin >> pId;
        cout << "  Doctor  ID : "; cin >> dId;

        if (!findPatient(pId)) { cout << "  Invalid Patient ID!\n"; pause(); return; }
        if (!findDoctor(dId))  { cout << "  Invalid Doctor ID!\n";  pause(); return; }

        cout << "  Date (DD/MM/YYYY): "; cin >> date;
        cout << "  Time (HH:MM AM/PM): "; cin.ignore(); getline(cin, time);
        cout << "  Notes (optional): "; getline(cin, notes);

        appointments.emplace_back(nextAppointmentId++, pId, dId, date, time, notes);
        cout << "\n  ✔ Appointment booked! ID: " << nextAppointmentId - 1 << "\n";
        pause();
    }

    void viewAppointments() const {
        printHeader("ALL APPOINTMENTS");
        if (appointments.empty()) { cout << "  No appointments.\n"; pause(); return; }
        cout << left
             << setw(6)  << "AptID"
             << setw(12) << "PatientID"
             << setw(10) << "DoctorID"
             << setw(14) << "Date"
             << setw(10) << "Time"
             << setw(14) << "Status"
             << "Notes\n"
             << string(100, '-') << "\n";
        for (auto& a : appointments) a.display();
        pause();
    }

    void updateAppointmentStatus() {
        printHeader("UPDATE APPOINTMENT STATUS");
        int id; string status;
        cout << "  Appointment ID : "; cin >> id;
        cout << "  New Status (Scheduled/Completed/Cancelled): "; cin >> status;
        for (auto& a : appointments) {
            if (a.getAptId() == id) { a.setStatus(status);
                cout << "  ✔ Status updated!\n"; pause(); return; }
        }
        cout << "  Appointment not found!\n"; pause();
    }

    // ── BILLING ──────────────────────────────────────────────
    void generateBill() {
        printHeader("GENERATE BILL");
        int pId, dId;
        double med, room;

        cout << "  Patient ID : "; cin >> pId;
        cout << "  Doctor  ID : "; cin >> dId;

        Patient* p = findPatient(pId);
        Doctor*  d = findDoctor(dId);
        if (!p) { cout << "  Invalid Patient ID!\n"; pause(); return; }
        if (!d) { cout << "  Invalid Doctor ID!\n";  pause(); return; }

        cout << "  Medicine Charges (Rs.): "; cin >> med;
        cout << "  Room Charges (Rs.)    : "; cin >> room;

        bills.emplace_back(nextBillId++, pId, d->getFee(), med, room);
        cout << "\n  Bill generated! ID: " << nextBillId - 1 << "\n";
        bills.back().display();
        pause();
    }

    void payBill() {
        printHeader("PAY BILL");
        int id;
        cout << "  Bill ID: "; cin >> id;
        for (auto& b : bills) {
            if (b.getBillId() == id) {
                if (b.paid()) cout << "  Bill already paid!\n";
                else { b.markPaid(); cout << "  ✔ Payment successful!\n"; }
                pause(); return;
            }
        }
        cout << "  Bill not found!\n"; pause();
    }

    void viewBills() const {
        printHeader("ALL BILLS");
        if (bills.empty()) { cout << "  No bills generated.\n"; pause(); return; }
        for (auto& b : bills) b.display();
        pause();
    }

    // ── DASHBOARD / STATS ────────────────────────────────────
    void showDashboard() const {
        printHeader("HOSPITAL DASHBOARD - " + hospitalName);
        int admitted = 0;
        for (auto p : patients) if (p->admitted()) admitted++;

        cout << "\n";
        cout << "  ┌─────────────────────────────────────────┐\n";
        cout << "  │  🏥  " << left << setw(36) << hospitalName << "│\n";
        cout << "  ├─────────────────────────────────────────┤\n";
        cout << "  │  👨‍⚕️  Total Doctors    : " << left << setw(16) << doctors.size()    << "│\n";
        cout << "  │  🤒  Total Patients   : " << left << setw(16) << patients.size()   << "│\n";
        cout << "  │  🛏️  Admitted         : " << left << setw(16) << admitted           << "│\n";
        cout << "  │  👷  Total Staff      : " << left << setw(16) << staffList.size()  << "│\n";
        cout << "  │  📋  Appointments     : " << left << setw(16) << appointments.size()<< "│\n";
        cout << "  │  💰  Bills Generated  : " << left << setw(16) << bills.size()      << "│\n";
        cout << "  └─────────────────────────────────────────┘\n\n";
        pause();
    }

    // ── MAIN MENU ────────────────────────────────────────────
    void run() {
        int choice;
        do {
            cout << "\n\n";
            cout << "  ╔══════════════════════════════════════════╗\n";
            cout << "  ║   HOSPITAL MANAGEMENT SYSTEM             ║\n";
            cout << "  ║   " << left << setw(40) << hospitalName << "║\n";
            cout << "  ╠══════════════════════════════════════════╣\n";
            cout << "  ║  1.  Add Doctor                          ║\n";
            cout << "  ║  2.  View All Doctors                    ║\n";
            cout << "  ║  3.  Add Patient                         ║\n";
            cout << "  ║  4.  View All Patients                   ║\n";
            cout << "  ║  5.  Search Patient                      ║\n";
            cout << "  ║  6.  Add Staff                           ║\n";
            cout << "  ║  7.  View All Staff                      ║\n";
            cout << "  ║  8.  Book Appointment                    ║\n";
            cout << "  ║  9.  View All Appointments               ║\n";
            cout << "  ║  10. Update Appointment Status           ║\n";
            cout << "  ║  11. Generate Bill                       ║\n";
            cout << "  ║  12. Pay Bill                            ║\n";
            cout << "  ║  13. View All Bills                      ║\n";
            cout << "  ║  14. Dashboard / Statistics              ║\n";
            cout << "  ║  0.  Exit                                ║\n";
            cout << "  ╚══════════════════════════════════════════╝\n";
            cout << "  Enter Choice: ";
            cin >> choice;

            switch (choice) {
                case 1:  addDoctor();               break;
                case 2:  viewDoctors();             break;
                case 3:  addPatient();              break;
                case 4:  viewPatients();            break;
                case 5:  searchPatient();           break;
                case 6:  addStaff();                break;
                case 7:  viewStaff();               break;
                case 8:  bookAppointment();         break;
                case 9:  viewAppointments();        break;
                case 10: updateAppointmentStatus(); break;
                case 11: generateBill();            break;
                case 12: payBill();                 break;
                case 13: viewBills();               break;
                case 14: showDashboard();           break;
                case 0:
                    cout << "\n  Thank you for using Hospital Management System!\n\n";
                    break;
                default:
                    cout << "  Invalid choice! Try again.\n";
            }
        } while (choice != 0);
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================
int main() {
    cout << "\n\n";
    cout << "  ╔═══════════════════════════════════════════╗\n";
    cout << "  ║   WELCOME TO HOSPITAL MANAGEMENT SYSTEM  ║\n";
    cout << "  ║      Object-Oriented Programming C++     ║\n";
    cout << "  ╚═══════════════════════════════════════════╝\n\n";

    string hospitalName;
    cout << "  Enter Hospital Name: ";
    getline(cin, hospitalName);

    HospitalManagementSystem hms(hospitalName);
    hms.run();

    return 0;
}
