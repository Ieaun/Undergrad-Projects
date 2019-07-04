using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace ManagementUI_Test
{
    /// <summary>
    /// Interaction logic for MakeBooking.xaml
    /// </summary>
    public partial class MakeBooking : Window
    {
        // Variables are intialised
        List<Performance> performanceList = new List<Performance>();
        List<Play> playsList = new List<Play>();
        List<Customer> customerList = new List<Customer>();
        List<string> row = new List<string>();
        Seats seats;
        List<string> availableStallSeats = new List<string>();
        List<Seat> bookedSeats = new List<Seat>();
        int currentRowIndex;
        string currentArea;
        string performanceID = "0";
        Customer currentCustomer;
        double currentPrice = 0;
        
        // Constructor initalises the lists
        public MakeBooking()
        {
            InitializeComponent();
            updatePlayList(); // Updates the plays list box
            updateCustomerList(); // Updates the customer list box
            // Adds option to seat area combobox
            SeatAreaComboBox.Items.Add("Stalls");
            SeatAreaComboBox.Items.Add("Upper Circle");
            SeatAreaComboBox.Items.Add("Dress Circle");
        }

        // Updates and displays list of customers
        private void updateCustomerList() {
            // Updates the list of customers from the database
            customerList = SQL.CustomerSQL.QueryFromDB();

            CustomerListBox.Items.Clear();
            // Loops through the list adding them to the list box
            foreach (Customer customer in customerList)
            {
                // If the customer is a member a '(G)' is displayed next to their name
                if (customer.getIsGold())
                {
                    CustomerListBox.Items.Add(customer.getFirstName() + " " + customer.getLastName() + " (G)");
                }
                else {
                    CustomerListBox.Items.Add(customer.getFirstName() + " " + customer.getLastName());
                }
            }
        }

        // Updates and displays list of plays
        private void updatePlayList() {
            // Updates the list of plays from the database
            playsList = SQL.PlaySQL.QueryFromDB();
            // Loops through the lsit adding them to the list box
            foreach (Play item in playsList)
            {
                showComboBox.Items.Add(item.getName());
            }
            
            // Checks whether there are any plays in the list box
            if (showComboBox.Items.Count != 0)
            {
                // Sets the index to 0
                showComboBox.SelectedIndex = 0;
            }  
        }

        // Books a random seat for the customer
        private void bookButton_Click(object sender, RoutedEventArgs e)
        {
            // Checks if a customer is selected
            if (CustomerListBox.SelectedIndex == -1)
            {
                MessageBox.Show("Select a customer to book.");
                return;
            }

            // Sets the current customer from the customer list
            currentCustomer = customerList[CustomerListBox.SelectedIndex];

            // Checks if any seats have already been booked
            if (bookedSeats.Count == 0) {
                // Gets a random area
                Random rand = new Random();
                int num = rand.Next(1,3);
                int row;
                int seat;
                switch (num) {
                    case 1:
                        // Gets a random row and seat for that area and adds it to the database
                        row = rand.Next(0,11);
                        seat = rand.Next(0, seats.getStalls()[row].Count);
                        seats.getStalls()[row][seat] = "booked";
                        SQL.SeatSQL.UpdateSeats(seats, performanceID);
                        bookedSeats.Add(new Seat("Stalls", row, seat, "booked"));
                        currentPrice = playsList[showComboBox.SelectedIndex].getStallPrice();
                        break;

                    case 2:
                        // Gets a random row and seat for that area and adds it to the database
                        row = rand.Next(0, 4);
                        seat = rand.Next(0, seats.getUpperSeats()[row].Count);
                        seats.getUpperSeats()[row][seat] = "booked";
                        SQL.SeatSQL.UpdateSeats(seats, performanceID);
                        bookedSeats.Add(new Seat("Upper Circle", row, seat, "booked"));
                        currentPrice = playsList[showComboBox.SelectedIndex].getUpperPrice();
                        break;

                    case 3:
                        // Gets a random row and seat for that area and adds it to the database
                        row = rand.Next(0, 4);
                        seat = rand.Next(0, seats.getDressSeats()[row].Count);
                        seats.getDressSeats()[row][seat] = "booked";
                        SQL.SeatSQL.UpdateSeats(seats, performanceID);
                        bookedSeats.Add(new Seat("Dress Circle", row, seat, "booked"));
                        currentPrice = playsList[showComboBox.SelectedIndex].getDressPrice();
                        break;
                }
            }

            // Checks if the method is successful by adding the booking to the database
            if (SQL.BookingSQL.AddToDB(currentCustomer, performanceID, bookedSeats, currentPrice) == true)
            {
                MessageBox.Show("Booking made succesfully.");
            }
            else {
                MessageBox.Show("Booking was not made.");
                return;
            }
            currentPrice = 0; // Resets the current price
            bookedSeats.Clear(); // Clears the seats fields
            bookedSeatsListBox.Items.Clear();
            TotalPriceBlock.Text = currentPrice.ToString();
        }

        // Reserves the seats chosen and adds the bookign into the system
        private void reserveButton_Click(object sender, RoutedEventArgs e)
        {
            // Checks if a customer is selected
            if (CustomerListBox.SelectedIndex == -1)
            {
                MessageBox.Show("Select a customer to book.");
                return;
            }
            // Checks if a seat area has been selected
            if (SeatAreaComboBox.SelectedIndex == -1)
            {
                MessageBox.Show("Select a seating area.");
                return;
            }
            // Checks if a row has been selected
            if (SeatRowComboBox.SelectedIndex == -1)
            {
                MessageBox.Show("Select a seating row.");
                return;
            }
            // Checks if any seats have been reserved
            if (bookedSeats.Count == 0)
            {
                MessageBox.Show("At least 1 seat must be reserved.");
                return;
            }

            // Gets the selected customer
            currentCustomer = customerList[CustomerListBox.SelectedIndex];

            // Adds booking to the database 
            if (SQL.BookingSQL.AddToDB(currentCustomer, performanceID, bookedSeats, currentPrice) == true)
            {
                MessageBox.Show("Reservation made succesfully.");
            }
            else
            {
                MessageBox.Show("Reservation failed.");
            }

            // Resets the current price and clears the booked seats list
            currentPrice = 0;
            bookedSeats.Clear();
            bookedSeatsListBox.Items.Clear();
            TotalPriceBlock.Text = currentPrice.ToString();
        }

        // Updates the performance dates when a show is selected
        private void showComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string playName = showComboBox.SelectedItem.ToString();
            // Updates the list of performances from the database 
            string playID = SQL.PlaySQL.QueryID(playName);

            performanceList = SQL.PerformanceSQL.QueryFromDB(playID);

            DateTime date;
            DateComboBox.Items.Clear();
            // Loops through the list adding them to the list box
            foreach (Performance performance in performanceList)
            {
                // Checks if the performance is within 6 months
                date = Convert.ToDateTime(performance.getDate());
                if (DateTime.Now.AddMonths(6).CompareTo(date) > 0)
                {
                    DateComboBox.Items.Add(performance.getDate());
                }
            }
            // If there are items in the combobox display item at index 0
            if (DateComboBox.Items.Count != 0)
            {
                DateComboBox.SelectedIndex = 0;
            }
        }

        // Gets the seats when a date is selected
        private void dateComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                performanceID = SQL.PerformanceSQL.QueryID(DateComboBox.SelectedItem.ToString());
                seats = SQL.SeatSQL.ReturnSeats(performanceID);
            }
            catch (Exception) {
            }
        }

        // Returns to the main page
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            ViewBookings man = new ViewBookings();
            this.Close();
            man.ShowDialog();
        }

        // Resets the price when a different customer is selected
        private void CustomerListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            currentPrice = 0;
            TotalPriceBlock.Text = currentPrice.ToString();
        }

        // Sets up the rows of seats when an area is selected
        private void SeatComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            SeatRowComboBox.Items.Clear(); // Clears the combobox
            // Sets the configuration to stalls
            if (SeatAreaComboBox.SelectedItem.ToString().Equals("Stalls"))
            {
                currentArea = SeatAreaComboBox.SelectedItem.ToString();
                SeatRowComboBox.Items.Add("A");
                SeatRowComboBox.Items.Add("B");
                SeatRowComboBox.Items.Add("C");
                SeatRowComboBox.Items.Add("D");
                SeatRowComboBox.Items.Add("E");
                SeatRowComboBox.Items.Add("D");
                SeatRowComboBox.Items.Add("F");
                SeatRowComboBox.Items.Add("G");
                SeatRowComboBox.Items.Add("H");
                SeatRowComboBox.Items.Add("J");
                SeatRowComboBox.Items.Add("K");
                SeatRowComboBox.Items.Add("L");
                SeatRowComboBox.Items.Add("M");

            }
            // Sets the configuration to upper circle
            else if (SeatAreaComboBox.SelectedItem.ToString().Equals("Upper Circle"))
            {
                currentArea = SeatAreaComboBox.SelectedItem.ToString();
                SeatRowComboBox.Items.Add("A");
                SeatRowComboBox.Items.Add("B");
                SeatRowComboBox.Items.Add("C");
                SeatRowComboBox.Items.Add("D");
                SeatRowComboBox.Items.Add("E");
            }
            // Sets the configuration to dress circle
            else if (SeatAreaComboBox.SelectedItem.ToString().Equals("Dress Circle"))
            {
                currentArea = SeatAreaComboBox.SelectedItem.ToString();
                SeatRowComboBox.Items.Add("A");
                SeatRowComboBox.Items.Add("B");
                SeatRowComboBox.Items.Add("C");
                SeatRowComboBox.Items.Add("D");
                SeatRowComboBox.Items.Add("E");
            }
        }

        // Loads the list of seats when a row is selected
        private void SeatRow_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                SeatsListBox.Items.Clear();
                switch (SeatRowComboBox.SelectedItem.ToString())
                {
                    case "A":
                        currentRowIndex = 0;
                        break;
                    case "B":
                        currentRowIndex = 1;
                        break;
                    case "C":
                        currentRowIndex = 2;
                        break;
                    case "D":
                        currentRowIndex = 3;
                        break;
                    case "E":
                        currentRowIndex = 4;
                        break;
                    case "F":
                        currentRowIndex = 5;
                        break;
                    case "G":
                        currentRowIndex = 6;
                        break;
                    case "H":
                        currentRowIndex = 7;
                        break;
                    case "J":
                        currentRowIndex = 8;
                        break;
                    case "K":
                        currentRowIndex = 9;
                        break;
                    case "L":
                        currentRowIndex = 10;
                        break;
                    case "M":
                        currentRowIndex = 11;
                        break;
                }
                row = seats.ReturnRow(SeatAreaComboBox.SelectedItem.ToString(), currentRowIndex);
            }
            catch (Exception) { }
            int counter = 0;

            // Displays the seat to the list
            foreach (string seat in row) {
                counter++;
                SeatsListBox.Items.Add(counter + "   -   " + seat);
            }
        }

        // Books a seat when the button is clicked
        private void AddSeatButton_Click(object sender, RoutedEventArgs e)
        {
            // Validation
            if (SeatsListBox.SelectedIndex == -1)
            {
                MessageBox.Show("Select a seat to book.");
                return;
            }
            if (CustomerListBox.SelectedIndex == -1)
            {
                MessageBox.Show("Select a Customer.");
                return;
            }
            if (bookedSeats.Count == 6)
            {
                MessageBox.Show("Only 6 Seats can be booked at a time.");
                return;
            }

            // Marks the seat as booked and checks if it was successful
            if (seats.bookSeat(currentArea, currentRowIndex, SeatsListBox.SelectedIndex) == true)
            {
                // Checks current area
                switch (currentArea)
                {
                    // Adds the seat price to the total price taking off 10% if the customer is a member
                    case "Stalls":
                        if (customerList[CustomerListBox.SelectedIndex].getIsGold() == true)
                        {
                            currentPrice += 0.9 * playsList[showComboBox.SelectedIndex].getStallPrice();
                        }
                        else
                        {
                            currentPrice += playsList[showComboBox.SelectedIndex].getStallPrice();
                        }
                        break;
                    // Adds the seat price to the total price taking off 10% if the customer is a member
                    case "Upper Circle":
                        if (customerList[CustomerListBox.SelectedIndex].getIsGold() == true)
                        {
                            currentPrice += 0.9 * playsList[showComboBox.SelectedIndex].getUpperPrice();
                        }
                        else
                        {
                            currentPrice += playsList[showComboBox.SelectedIndex].getUpperPrice();
                        }
                        break;
                    // Adds the seat price to the total price taking off 10% if the customer is a member
                    case "Dress Circle":
                        if (customerList[CustomerListBox.SelectedIndex].getIsGold() == true)
                        {
                            currentPrice += 0.9 * playsList[showComboBox.SelectedIndex].getDressPrice();
                        }
                        else
                        {
                            currentPrice += playsList[showComboBox.SelectedIndex].getDressPrice();
                        }
                        break;
                }
                // Displays preice to screen, adds seat to list of booked seats then updates the seats
                TotalPriceBlock.Text = currentPrice.ToString();
                bookedSeats.Add(new Seat(currentArea, currentRowIndex, SeatsListBox.SelectedIndex, seats.getSeatAt(currentArea, currentRowIndex, SeatsListBox.SelectedIndex))); // Adds it to a new list
                updateSeatLists();
            }
            else
            {
                MessageBox.Show("Seat is already reserved.");
                return;
            }
        }

        // Used to remove a seat form the booked seats list
        private void RemoveSeatButton_Click(object sender, RoutedEventArgs e)
        {
            // Checks if there are any booked seats
            if (bookedSeatsListBox.Items.Count != 0)
            {
                // Sets the index to 0
                bookedSeatsListBox.SelectedIndex = 0;
                try
                {
                    // Checks the current area
                    switch (currentArea)
                    {
                        // Subtracts the seat price to the total price taking off 10% if the customer is a member
                        case "Stalls":
                            if (customerList[CustomerListBox.SelectedIndex].getIsGold() == true)
                            {
                                currentPrice -= 0.9 * playsList[showComboBox.SelectedIndex].getStallPrice();
                            }
                            else
                            {
                                currentPrice -= playsList[showComboBox.SelectedIndex].getStallPrice();
                            }
                            break;
                        // Subtracts the seat price to the total price taking off 10% if the customer is a member
                        case "Upper Circle":
                            if (customerList[CustomerListBox.SelectedIndex].getIsGold() == true)
                            {
                                currentPrice -= 0.9 * playsList[showComboBox.SelectedIndex].getUpperPrice();
                            }
                            else
                            {
                                currentPrice -= playsList[showComboBox.SelectedIndex].getUpperPrice();
                            }
                            break;
                        // Subtracts the seat price to the total price taking off 10% if the customer is a member
                        case "Dress Circle":
                            if (customerList[CustomerListBox.SelectedIndex].getIsGold() == true)
                            {
                                currentPrice -= 0.9 * playsList[showComboBox.SelectedIndex].getDressPrice();
                            }
                            else
                            {
                                currentPrice -= playsList[showComboBox.SelectedIndex].getDressPrice();
                            }
                            break;
                    }
                }
                catch (Exception)
                {
                    MessageBox.Show("Select a Customer.");
                    return;
                }
                // Displays preice to screen, removes seat from list of booked seats then updates the seats
                TotalPriceBlock.Text = currentPrice.ToString();
                seats.unbookSeat(bookedSeats[bookedSeatsListBox.SelectedIndex]);
                bookedSeats.RemoveAt(bookedSeatsListBox.SelectedIndex);
                updateSeatLists();
            }
        }

        // Updates the Seats in the database
        private void updateSeatLists() {
            // Updates the database using the current seats and performance
            SQL.SeatSQL.UpdateSeats(seats, performanceID);
            // Clears the listbox
            bookedSeatsListBox.Items.Clear();
            // Loops through list of booked seats and adds them to the listbox
            foreach (Seat seat in bookedSeats)
            {
                bookedSeatsListBox.Items.Add(seat.getArea() + "-" + SeatRowComboBox.SelectedItem.ToString() + " - " + (seat.getSeatIndex() + 1) + " - " + seat.getStatus());
            }

            // Updates the list of all seats
            SeatsListBox.Items.Clear();
            row = seats.ReturnRow(SeatAreaComboBox.SelectedItem.ToString(), currentRowIndex);
            int counter = 0;
            foreach (string seat in row)
            {
                counter++;
                SeatsListBox.Items.Add(counter + "   -   " + seat);
            }
        }
    }
}
