#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// movie details store karne ke liye structure
struct movie {
    int id;
    char title[40];
    int price;
    char duration[15];
    char timing[15];
    int seat[5][6]; // 5 rows aur 6 columns = 30 seats
} movies[5];

// customer booking details store karne ke liye structure
struct Booking {
    int bookingId;
    char name[50];
    char phone[15];
    int movieId; 
    char timings[15];
    int seatCount;
    int seatIndices[6];
    float baseAmount;
    float gstAmount;
    float totalAmount;
    int isCancelled;
};

struct Booking bookings[50];
int nextBookingId = 1001;
int bookingCount = 0;

// sample data
char Movies[5][40] = {
    "Kabir Singh",
    "Vivarium",
    "Source Code",
    "Forrest Gump",
    "Love & Other Drugs"
};

char Durations[5][15] = {
    "2h 52m",
    "1h 38m",
    "1h 33m",
    "2h 22m",
    "1h 52m"
};

int Prices[5] = {150, 250, 350, 450, 550};

char timings[5][15] = {
    "10:00 AM",
    "01:45 PM",
    "04:15 PM",
    "06:40 PM",
    "09:55 PM"
};

// functions ke declarations (prototypes)
int getValidInt(int min, int max);
int isValidPhone(char phone[]);
int checkName(char name[]);
void displayMovies();
void showTimings();
void displaySeats(int movieID);
void checkSeatAvailability();
void bookTickets();
void cancelTickets();
void viewBill();
void printBill(struct Booking *b);

int main() {
    int choice;

    // shuru me saare movies ka data set kar rahe hai aur seats 0 (available) kar rahe hai
    for (int i = 0; i < 5; i++) {
        movies[i].id = i + 1;
        strcpy(movies[i].title, Movies[i]);
        movies[i].price = Prices[i];
        strcpy(movies[i].duration, Durations[i]);
        strcpy(movies[i].timing, timings[i]);

        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 6; c++) {
                movies[i].seat[r][c] = 0;
            }
        }
    }

    // main menu loop jab tak user 7 press na kare
    while (1) {
        printf("\n============================================================\n");
        printf("        *** MOVIE TICKET BOOKING SYSTEM (MCA) ***           \n");
        printf("============================================================\n");
        printf("  1. Display Movies\n");
        printf("  2. Show Timings\n");
        printf("  3. Seat Availability\n");
        printf("  4. Book Tickets\n");
        printf("  5. Cancel Tickets\n");
        printf("  6. Generate / View Bill\n");
        printf("  7. Exit\n");
        printf("============================================================\n");
        printf("Enter your choice (1-7): ");

        choice = getValidInt(1, 7);

        switch (choice) {
            case 1: 
                displayMovies(); 
                break;
            case 2: 
                showTimings(); 
                break;
            case 3: 
                checkSeatAvailability(); 
                break;
            case 4: 
                bookTickets(); 
                break;
            case 5: 
                cancelTickets(); 
                break;
            case 6: 
                viewBill(); 
                break;
            case 7:
                printf("\nThank you for using Movie Ticket Booking System! Goodbye.\n");
                return 0;
        }
    }
    return 0;
}

// safe integer input lene ke liye taaki alphabets daalne par loop na phase
int getValidInt(int min, int max) {
    int value;
    while(1) {
        if(scanf("%d", &value) == 1) {
            while(getchar() != '\n'); // bacha hua newline saaf kiya
            if(value >= min && value <= max) {
                return value;
            } else {
                printf("Invalid choice! Enter between %d to %d: ", min, max);
            }
        } else {
            while(getchar() != '\n'); // galat characters ko buffer se hataya
            printf("Invalid input! Please enter a valid number: ");
        }
    }
}

// 10 digit ka mobile number check karne ke liye
int isValidPhone(char phone[]) {
    int len = strlen(phone);
    if(len != 10) return 0;

    for(int i = 0; i < len; i++) {
        if(phone[i] < '0' || phone[i] > '9') return 0;
    }
    return 1;
}

// naam kam se kam 4 character ka hona chahiye
int checkName(char name[]) {
    while(1) {
        if(scanf(" %[^\n]", name) == 1) {
            while(getchar() != '\n');
            if(strlen(name) > 3) {
                return 1;
            } else {
                printf("Name must be 4 characters minimum!!\n");
                continue;
            }
        } else {
            printf("Invalid Input\n");
        }
    }
}

// movies ki list print karta hai
void displayMovies() {
    printf("\n==================================================================================\n");
    printf("                 NOW SHOWING MOVIES                    \n");
    printf("==================================================================================\n");
    printf("%-5s | %-28s | %-12s | %-12s\n", "ID", "Movie Title", "Duration", "Price");
    printf("----------------------------------------------------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("%-5d | %-28s | %-12s | Rs. %d\n", i + 1, Movies[i], Durations[i], Prices[i]);
    }
    printf("=======================================================\n");
}

// selected movie ka show time dikhane ke liye
void showTimings() {
    printf("\n Enter Movie ID to view timings: ");
    int movieID = getValidInt(1, 5) - 1;
    
    printf("\n===================================================================================\n");
    printf("                        DAILY SHOWS OF %s                                            \n", movies[movieID].title);
    printf("===================================================================================\n");
    printf("%-5s | %-20s | %-10s | %-12s\n", "ID", "Movie Title", "Duration", "Show Time");
    printf("----------------------------------------------------------------------------------\n");
    printf("%-5d | %-20s | %-10s | %-12s\n", 
           movies[movieID].id, movies[movieID].title, movies[movieID].duration, movies[movieID].timing);
    printf("========================================================================\n");
}

// 5x6 ka theater layout dikhane ke liye
void displaySeats(int movieID) {
    int availability = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 6; j++) {
            if(movies[movieID].seat[i][j] == 0) availability++;
        }
    }
    printf("\n=======================================================\n");
    printf(" SEAT LAYOUT: %s [%s]\n", movies[movieID].title, movies[movieID].timing);
    printf(" Available Seats: %d / %d\n", availability, 30);
    printf("=======================================================\n");
    printf("               ________________________\n");
    printf("              |         SCREEN         |\n");
    printf("              |________________________|\n\n");

    printf("         1    2    3    4    5    6\n");
    for(int i = 0; i < 5; i++) {
        printf("  [%c]  ", 'A' + i);
        for(int j = 0; j < 6; j++) {
            if(movies[movieID].seat[i][j] == 0) {
                printf(" [%-2d]", i * 6 + j + 1);
            } else {
                printf(" [X] ");
            }
        }
        printf("\n");
    }
    printf("\n  Legend: [0] = Available   [X] = Booked\n");
    printf("=======================================================\n");
}

void checkSeatAvailability() {
    displayMovies();
    printf("\nEnter movie id to check seat availability: ");
    int movieID = getValidInt(1, 5) - 1;
    displaySeats(movieID);
}

// ticket booking function
void bookTickets() {
    displayMovies();
    printf("Enter Movie Id: ");
    int movieID = getValidInt(1, 5) - 1;

    printf("\nEnter the Number Of Seats You Want To book: ");
    int totalTickets = getValidInt(1, 6);

    displaySeats(movieID);
    int selected[totalTickets];

    for(int i = 0; i < totalTickets; i++) {
        while(1) {
            printf("Enter Seat Number: ");
            int seatChoice = getValidInt(1, 30);

            // row aur column nikalne ka logic
            int row = (seatChoice - 1) / 6;
            int col = (seatChoice - 1) % 6;

            // pehle se booked seat check kiya
            if(movies[movieID].seat[row][col] == 1) {
                printf("Seat already Taken! Try Again\n");
                continue;
            }

            // user ne same seat do baar select na kiya ho
            int isDup = 0;
            for(int j = 0; j < i; j++) {
                if(selected[j] == seatChoice - 1) {
                    printf("Seat Already Selected! Try Again\n");
                    isDup = 1;
                    break;
                }
            }
            if(isDup) continue;

            selected[i] = seatChoice - 1;
            break;
        }
    }
        
    char custName[20];
    char custMobil[15];

    printf("\n Enter customer Name: ");
    checkName(custName);

    while(1) {
        printf("\n ENter Phone Number : ");
        scanf(" %[^\n]", custMobil);
        if(isValidPhone(custMobil)) {
            break;
        }
        printf("  invalid phone number! Must be exactly 10 digits (0-9).\n");
    }

    printf("\nConfirm booking? (1 for YES, 2 for NO): ");
    int confirm = getValidInt(1, 2);
    if (confirm != 1) {
        printf("  [x] Booking cancelled. No seats reserved.\n");
        return;
    }

    // seats ko 1 mark karke book kiya
    for(int i = 0; i < totalTickets; i++) {
        movies[movieID].seat[(selected[i] / 6)][(selected[i] % 6)] = 1;
    }

    // booking record save kiya
    struct Booking *b = &bookings[bookingCount];
    b->bookingId = nextBookingId++;
    b->movieId = movieID;
    strcpy(b->timings, movies[movieID].timing);
    strcpy(b->name, custName);
    strcpy(b->phone, custMobil);

    b->seatCount = totalTickets;
    for(int i = 0; i < totalTickets; i++) {
        b->seatIndices[i] = selected[i];
    }
    b->baseAmount = movies[movieID].price * totalTickets;
    b->gstAmount = b->baseAmount * 0.18f;
    b->totalAmount = b->baseAmount + b->gstAmount;
    b->isCancelled = 0;

    bookingCount++;
    
    printf("\nBooking Confirmed!\n");
    printf("Booking ID: %d\n", b->bookingId);
    printf("Movie: %s\n", movies[b->movieId].title);
    printf("Show Time: %s\n", b->timings);
    
    printf("\n  [✓] Booking Confirmed Successfully!\n");
    printf("\n  [✓] Booking ID is :%d\n", b->bookingId);
    printBill(b);
}

// ticket cancel karne ka function
void cancelTickets() {
    if(bookingCount == 0) {
        printf("NO booking done yet\n");
        return;
    }
    int found = -1;
    printf("Enter Booking Id to Cancel: ");
    int bid = getValidInt(1001, 9999);
    for(int i = 0; i < bookingCount; i++) {
        if(bookings[i].bookingId == bid) {
            found = 1;
            struct Booking *b = &bookings[i];
            if(b->isCancelled == 1) {
                printf("already cancelled\n");
                return;
            } else {
                b->isCancelled = 1;
                // seat ko wapas 0 (available) kar diya
                for(int s = 0; s < b->seatCount; s++) {
                    int idx = b->seatIndices[s];
                    movies[b->movieId].seat[idx / 6][idx % 6] = 0;
                }
                printf("\nBooking cancelled\n");
            }
            return;
        }
    }
    if(found == -1) {
        printf("Booking Id not found\n");
    }
}

// bill print karne ka function
void printBill(struct Booking *b) {
    printf("\n============================================================\n");
    printf("                    CINEMA TICKET INVOICE                   \n");
    printf("============================================================\n");
    printf(" Booking ID     : %d\n", b->bookingId);
    printf(" Status         : %s\n", b->isCancelled ? "CANCELLED" : "CONFIRMED / ACTIVE");
    printf(" Customer Name  : %s\n", b->name);
    printf(" Contact Phone  : %s\n", b->phone);
    printf("------------------------------------------------------------\n");
    printf(" Movie Title    : %s\n", movies[b->movieId].title);
    printf(" Show Timing    : %s\n", b->timings);
    printf(" Total Tickets  : %d\n", b->seatCount);
    printf(" Reserved Seats : ");
    for (int i = 0; i < b->seatCount; i++) {
        printf("%d ", b->seatIndices[i] + 1);
    }
    printf("\n------------------------------------------------------------\n");
    printf(" Base Fare      : Rs. %8.2f\n", b->baseAmount);
    printf(" GST (18%%)      : Rs. %8.2f\n", b->gstAmount);
    printf(" Grand Total    : Rs. %8.2f\n", b->totalAmount);
    printf("============================================================\n");
    printf("   Thank you for booking with us! Enjoy your movie!\n");
    printf("============================================================\n");
}

// purana bill dekhne ke liye
void viewBill() {
    int found = -1;
    if(bookingCount == 0) {
        printf("No booking done yet\n");
    } else {
        printf("Enter Booking Id: ");
        int bid = getValidInt(1001, 9999);
        for(int i = 0; i < bookingCount; i++) {
            if(bookings[i].bookingId == bid) {
                struct Booking *b = &bookings[i];
                printBill(b);
                found = 1;
                break;
            }
        }
        if(found == -1) {
            printf("Booking id not Found\n");
        }
    }
}
