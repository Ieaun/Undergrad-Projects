using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SQLite;

namespace ManagementUI_Test.SQL
{
    public class BookingSQL
    {
        /// <summary>
        /// Adds a booking entry to the booking table of the database
        /// </summary>
        /// <param name="customer"></param> Customer object
        /// <param name="performanceID"></param>
        /// <param name="bookedSeats"></param> List of seats booked by customer
        /// <param name="price"></param>
        /// <returns>
        /// Returns a bool value so can be checked if it has worked successfully
        /// </returns>
        public static bool AddToDB(Customer customer, string performanceID, List<Seat> bookedSeats, double price)
        {
            // Gets a connection
            SQLiteConnection dbConnection = CreateSQL.ReturnConn();
            dbConnection.Open();

            string seats = "";
            // Seats are added to a string
            foreach (Seat seat in bookedSeats) {
                seats = seat.getArea() + "/" + seat.getRowIndex() + "/" + seat.getSeatIndex() + "|" + seats; 
            }

            // Creates the query string using parameters passed in
            string query = "INSERT INTO Bookings (PerformanceID, CustomerID, Date, Price, Seats) VALUES (" +
                "" + performanceID + " , " + customer.getID() + ", '" + DateTime.Now + "', " + price + ", '" + seats + "')";
            SQLiteCommand command = new SQLiteCommand(query, dbConnection);
            command.ExecuteNonQuery(); // Creates and excutes the command
            dbConnection.Close(); // Closes connection
            return true; // Returns true so that the amin code can check if it was successful
        }

        /// <summary>
        /// Removes a booking from the table
        /// </summary>
        /// <param name="booking"></param> Booking object
        public static void DeleteFromDB(Booking booking)
        {
            // Gets a connection
            SQLiteConnection dbConnection = CreateSQL.ReturnConn();
            dbConnection.Open();

            // Creates the query string using data passed in
            string query = "DELETE FROM Bookings  WHERE Booking = " +
                booking.getID() + ";";

            // Creates and executes the command
            SQLiteCommand command = new SQLiteCommand(query, dbConnection);
            command.ExecuteNonQuery();
            dbConnection.Close(); // Closes the connection
        }

        /// <summary>
        /// Returns a list of all the bookings
        /// </summary>
        public static List<Booking> QueryFromDB()
        {
            // Gets a connection
            SQLiteConnection dbConnection = CreateSQL.ReturnConn();
            dbConnection.Open();

            // Creates the query string
            string query = "SELECT * FROM Bookings;";

            // Creates and execute the command
            SQLiteCommand command = new SQLiteCommand(query, dbConnection);
            SQLiteDataReader reader = command.ExecuteReader();
            int counter = 0;
            string seatString = "";
            List<Seat> seatList = new List<Seat>();
            string[] seats;
            // Creates the list and adds each booking to it
            List<Booking> list = new List<Booking>();
            while (reader.Read())
            {
                // Gets the seats string and adds it to the booking as seat objects
                seatString = reader[5].ToString();
                foreach (string seatInfo in seatString.Split('|'))
                {
                    seats = seatInfo.Split('/');
                    if (!seatInfo.Equals(""))
                    {
                        seatList.Add(new Seat(seats[0], int.Parse(seats[1]), int.Parse(seats[2]), "booked"));
                    }
                }
                list.Add(new Booking(int.Parse(reader[0].ToString()), int.Parse(reader[1].ToString()), int.Parse(reader[2].ToString()), reader[3].ToString(), Convert.ToDouble(reader[4])));
                list[counter].setSeats(seatList);
                counter++;
            }
            dbConnection.Close(); // Closes connection

            // Returns the list of bookings
            return list;

        }
    }
}