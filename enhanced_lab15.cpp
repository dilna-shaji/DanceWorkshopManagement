#include <iostream>
#include <string>

using namespace std;

// Class to store payment details for each student
class PaymentDetails {
protected:
    double fees;                 // Stores the fees amount
    string payment_method;       // Stores the payment method (e.g., Cash, Card)

public:
    // Default constructor
    PaymentDetails() : fees(0.0), payment_method("Unknown") {}

    // Parameterized constructor to initialize fees and payment method
    PaymentDetails(double f, string method) : fees(f), payment_method(method) {}

    // Display the payment details for a student
    void displayPaymentDetails() {
        cout << "Fees: $" << fees << endl;
        cout << "Payment Method: " << payment_method << endl;
    }
};

// Derived class representing a dance workshop with student details
class DanceWorkshop : public PaymentDetails {
private:
    int reg_no;                 // Registration number of the student
    string name_of_the_student; // Name of the student
    int age;                    // Age of the student
    string category;            // Dance category (e.g., Ballet, Hip Hop)
    string contact_no;          // Contact number of the student

    static double GST_RATE;     // GST rate applied on fees
    static int student_count;   // Counter for number of students registered

public:
    // Default constructor
    DanceWorkshop() : reg_no(0), name_of_the_student("Unknown"), age(0), category("None"), contact_no("000-000-0000") {
        student_count++;
    }

    // Parameterized constructor to initialize student and payment details
    DanceWorkshop(int reg, string name, int a, string cat, string contact, double fee, string method)
        : reg_no(reg), name_of_the_student(name), age(a), category(cat), contact_no(contact), PaymentDetails(fee, method) {
        student_count++;
    }

    // Display details of the student and the payment details
    void displayDetails() {
        cout << "Registration No.: " << reg_no << endl;
        cout << "Student Name: " << name_of_the_student << endl;
        cout << "Age: " << age << endl;
        cout << "Category: " << category << endl;
        cout << "Contact No.: " << contact_no << endl;
        displayPaymentDetails();
    }

    // Static method to display total count of registered students
    static void displayStudentCount() {
        cout << "Total students registered: " << student_count << endl;
    }
};

// Initializing static member variables
double DanceWorkshop::GST_RATE = 0.18; // Example GST rate of 18%
int DanceWorkshop::student_count = 0;

int main() {
    // Create a student with payment details
    DanceWorkshop student1(101, "Alice Johnson", 20, "Ballet", "123-456-7890", 200.0, "Credit Card");

    cout << "Student Details:" << endl;
    student1.displayDetails();     // Display student and payment details

    cout << endl;
    DanceWorkshop::displayStudentCount(); // Display total number of students

    return 0;
}
