#include <iostream>
#include <string>

using namespace std;


class PaymentDetails {
protected:
    double fees;
    string payment_method;

public:
    PaymentDetails() : fees(0.0), payment_method("Unknown") {}

    PaymentDetails(double f, string method) : fees(f), payment_method(method) {}

    void displayPaymentDetails() {
        cout << "Fees: $" << fees << endl;
        cout << "Payment Method: " << payment_method << endl;
    }
};

class DanceWorkshop : public PaymentDetails {
private:
    int reg_no;
    string name_of_the_student;
    int age;
    string category;
    string contact_no;

    static double GST_RATE; 
    static int student_count;

public:
   
    DanceWorkshop() : reg_no(0), name_of_the_student("Unknown"), age(0), category("None"), contact_no("000-000-0000") {
        student_count++;
    }

    DanceWorkshop(int reg, string name, int a, string cat, string contact, double fee, string method)
        : reg_no(reg), name_of_the_student(name), age(a), category(cat), contact_no(contact), PaymentDetails(fee, method) {
        student_count++;
    }

    virtual ~DanceWorkshop() {
        student_count--;
    }

    virtual void displayDetails() {
        cout << "Registration Number: " << reg_no << endl;
        cout << "Name: " << name_of_the_student << endl;
        cout << "Age: " << age << endl;
        cout << "Category: " << category << endl;
        cout << "Contact Number: " << contact_no << endl;
        displayPaymentDetails();
    }

    DanceWorkshop& operator++() {
        fees += fees * GST_RATE; 
        return *this;
    }

    string operator[](string& attribute) {
        if (attribute == "name") return name_of_the_student;
        else if (attribute == "category") return category;
        else if (attribute == "contact") return contact_no;
        return "Invalid attribute"; 
    }

    int operator[](int index) {
        switch (index) {
            case 0: return reg_no;
            case 1: return age;
            default: return -1;
        }
    }

    double operator[](double index) {
        if (index == 0.0) return fees;
        return -1.0;
    }
};

double DanceWorkshop::GST_RATE = 0.18;
int DanceWorkshop::student_count = 0;

class AdvancedDanceWorkshop : public DanceWorkshop {
protected:
    string level;

public:
    AdvancedDanceWorkshop() : DanceWorkshop(), level("Beginner") {}

    AdvancedDanceWorkshop(int reg, string name, int a, string cat, string contact, double fee, string method, string lvl)
        : DanceWorkshop(reg, name, a, cat, contact, fee, method), level(lvl) {}


    virtual void displayDetails() override {
        DanceWorkshop::displayDetails();
        cout << "Level: " << level << endl; 
    }
};


class SpecializedDanceWorkshop : public AdvancedDanceWorkshop {
private:
    string specialization;

public:
    SpecializedDanceWorkshop() : AdvancedDanceWorkshop(), specialization("None") {}

    SpecializedDanceWorkshop(int reg, string name, int a, string cat, string contact, double fee, string method, string lvl, string spec)
        : AdvancedDanceWorkshop(reg, name, a, cat, contact, fee, method, lvl), specialization(spec) {}


    virtual void displayDetails() override {
        AdvancedDanceWorkshop::displayDetails();
        cout << "Specialization: " << specialization << endl; 
    }
};


class InstructorDetails {
protected:
    string instructor_name;

public:
    InstructorDetails() : instructor_name("Unknown") {}

    InstructorDetails(string name) : instructor_name(name) {}

    void displayInstructor() {
        cout << "Instructor Name: " << instructor_name << endl;
    }
};

class SpecialDanceWorkshop : public DanceWorkshop, public InstructorDetails {
public:
    SpecialDanceWorkshop(int reg, string name, int age, string cat, string contact, double fee, string method, string instr)
        : DanceWorkshop(reg, name, age, cat, contact, fee, method), InstructorDetails(instr) {}


    virtual void displayDetails() override {
        DanceWorkshop::displayDetails();
        displayInstructor();
    }
};

int main() {
    int num_students;
    cout << "Enter the number of students: ";
    cin >> num_students;

    DanceWorkshop** students = new DanceWorkshop*[num_students];

    for (int i = 0; i < num_students; i++) {
        int reg;
        string name;
        int age;
        string category;
        string contact;
        double fee;
        string method, level, specialization, instructor;
        char choice;

        cout << "\nEnter details for student " << (i + 1) << ":\n";
        cout << "Enter Registration Number: ";
        cin >> reg;

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Category: ";
        cin >> category;

        cout << "Enter Contact Number: ";
        cin >> contact;

        cout << "Enter Fees: ";
        cin >> fee;

        cout << "Enter Payment Method: ";
        cin >> method;

        cout << "Is this student in an advanced workshop? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            cout << "Enter Level (Beginner/Intermediate/Advanced): ";
            cin >> level;

            cout << "Does this student have a specialization? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                cout << "Enter Specialization (e.g., Ballet, Hip-hop): ";
                cin >> specialization;

                students[i] = new SpecializedDanceWorkshop(reg, name, age, category, contact, fee, method, level, specialization);
            } else {
                
                students[i] = new AdvancedDanceWorkshop(reg, name, age, category, contact, fee, method, level);
            }
        } else {
            cout << "Is this student in a special workshop with an instructor? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cout << "Enter Instructor Name: ";
                cin >> instructor;

                students[i] = new SpecialDanceWorkshop(reg, name, age, category, contact, fee, method, instructor);
            } else {
                students[i] = new DanceWorkshop(reg, name, age, category, contact, fee, method);
            }
        }

        ++(*students[i]);

        cout << "\nDetails for student " << (i + 1) << " (including GST):\n";
        students[i]->displayDetails();
    }

    for (int i = 0; i < num_students; i++) {
        delete students[i];
    }
    delete[] students;

    return 0;
}

