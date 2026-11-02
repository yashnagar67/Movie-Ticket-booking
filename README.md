# Movie-Ticket-booking
# 🎬 Movie Booking System — Simple Presentation Notes

> **Quick 5-Minute Guide for Presentation & Viva**  
> Everything is explained in plain, simple English so you and your partner can explain the project effortlessly.

---

## 🎯 1. What Does This Project Do?
A cinema ticket booking program in C with **6 main features**:
1. **Display Movies:** Shows the 5 movies, runtimes, and prices.
2. **Show Timings:** Shows movie showtimes (10:00 AM to 12:00 AM with ~52-minute cleaning breaks).
3. **Seat Availability:** Shows a visual 5x6 hall with seats numbered `1` to `30`.
4. **Book Tickets:** Lets a customer book 1 to 6 seats, takes name and phone, and calculates the total with 18% GST.
5. **Cancel Tickets:** Enters Booking ID (e.g., 1001), releases seats back to available, and marks ticket cancelled.
6. **View Bill:** Reprints the customer invoice anytime using their Booking ID.

---

## 🧠 2. The 2 Main Structures (Easy Explanation)

### A. `struct movie` (The Movie Details)
Stores information about each movie:
```c
struct movie {
    int id;             // Movie number (1 to 5)
    char title[40];     // Name of movie (e.g. "Kabir Singh")
    int price;          // Ticket price (e.g. 150)
    char duration[15];  // Runtime (e.g. "2h 52m")
    char timing[15];    // Show time (e.g. "10:00 AM")
    int seat[5][6];     // The 30 seats: 0 = Free, 1 = Booked
} movies[5];
```

### B. `struct Booking` (The Customer Receipt)
Stores each customer's booking transaction:
```c
struct Booking {
    int bookingId;       // Unique ID: 1001, 1002, 1003...
    char name[50];       // Customer's name
    char phone[15];      // 10-digit mobile number
    int movieId;         // Which movie they booked
    char timings[15];    // Time of show
    int seatCount;       // Number of tickets (e.g. 2)
    int seatIndices[6];  // The seat numbers booked
    float baseAmount;    // Ticket price * number of tickets
    float gstAmount;     // 18% GST
    float totalAmount;   // Final amount to pay
    int isCancelled;     // 0 = Active, 1 = Cancelled
};
struct Booking bookings[50];
```

---

## 🛠️ 3. Function Cheatsheet (Who Does What?)

```
              ┌─── 1. displayMovies()          --> Prints movie list & prices
              ├─── 2. showTimings()            --> Prints show schedule
              ├─── 3. checkSeatAvailability()  --> Calls displaySeats() to draw hall
main() Menu ──┼─── 4. bookTickets()            --> Takes seats, name, phone & books
              ├─── 5. cancelTickets()          --> Frees seats & cancels booking
              ├─── 6. viewBill()               --> Calls printBill() to show receipt
              └─── 7. Exit                     --> Closes program
```

### Plain English Summary of Each Function:
* **`getValidInt(min, max)`**: Takes a number from user. If user types letters or a wrong number, it asks again without crashing.
* **`isValidPhone(phone)`**: Makes sure phone has exactly 10 digits (all 0-9).
* **`checkName(name)`**: Makes sure customer name is at least 4 letters long.
* **`displaySeats(movieID)`**: Draws the screen and the 30 seats. Shows available seats as numbers (`1` to `30`) and booked seats as `[X]`.
* **`bookTickets()`**:
  1. Asks how many seats (1 to 6).
  2. Asks for each seat number. Checks: Does seat exist? Is it already `[X]`? Did you type it twice?
  3. Takes name and phone number.
  4. Marks seats as `1` (Booked) and saves the booking.
* **`cancelTickets()`**: Takes Booking ID. Sets `isCancelled = 1` and turns those seats back into `0` (Available).
* **`printBill(b)`**: Prints the clean invoice with Base Fare, 18% GST, and Grand Total.

---

## 🧮 4. The Seat Math (Super Simple!)

The user sees seats **1 to 30**, but the computer stores them in a **5-row by 6-column grid** (`seat[5][6]`):

$$\text{Row} = \frac{\text{Seat} - 1}{6}$$
$$\text{Column} = (\text{Seat} - 1) \% 6$$

### Example: If user picks Seat 15
1. Subtract 1: $15 - 1 = 14$
2. $\text{Row} = 14 / 6 = \mathbf{2}$ (Row C)
3. $\text{Column} = 14 \% 6 = \mathbf{2}$ (Column 3)
4. Computer marks: `movies[m].seat[2][2] = 1`

*(Division `/` gives row, Modulo `%` gives column. That's all!)*

---

## 🗣️ 5. Teacher Viva Questions (Memorize These 4 Lines!)

### Q1: Why do we write `while(getchar() != '\n');`?
> **Answer:**  
> *"If someone enters letters into `scanf("%d")`, the characters get stuck in the input buffer and cause an infinite loop. `while(getchar() != '\n');` clears and empties the buffer."*

### Q2: What does `scanf(" %[^\n]", name);` do?
> **Answer:**  
> *"The space on the left ignores any leftover Enter key. `%[^\n]` allows reading full names with spaces until the user presses Enter."*

### Q3: How does ticket cancellation release seats?
> **Answer:**  
> *"We find the booking by ID. We set `isCancelled = 1`, and we change the booked seat numbers back to `0` in `movies[m].seat[row][col] = 0`."*

### Q4: Why do we use `%8.2f` for money on the bill?
> **Answer:**  
> *"The `8` right-aligns the number so all decimal points line up in a straight vertical column, and `.2` shows 2 decimal digits."*
