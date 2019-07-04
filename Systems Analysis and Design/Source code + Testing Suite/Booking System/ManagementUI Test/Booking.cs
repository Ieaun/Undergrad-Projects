using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagementUI_Test
{
    /// <summary>
    /// Booking object used to store information of bookings
    /// </summary>
    public class Booking
    {
        // Private members
        private int id;
        private int performanceID;
        private int customerID;
        private string date;
        private double price;
        private List<Seat> bookedSeats;

        // Constructor to assign local members values
        public Booking(int pID, int pPerformanceID, int pCustomerID, string pDate, double pPrice) {
            this.setID(pID);
            this.setPerformanceID(pPerformanceID);
            this.setCustomerID(pCustomerID);
            this.setDate(pDate);
            this.setPrice(pPrice);
        }

        // Setters
        public void setID(int pID) { this.id = pID; }
        public void setPerformanceID(int pPerformanceID) { this.performanceID = pPerformanceID; }
        public void setCustomerID(int pCustomerID) { this.customerID = pCustomerID; }
        public void setDate(string pDate) { this.date = pDate; }
        public void setPrice(double pPrice) { this.price = pPrice; }
        public void setSeats(List<Seat> pBookedSeats) { this.bookedSeats = pBookedSeats; }

        // Getters
        public int getID() { return this.id; }
        public int getPerformanceID() { return this.performanceID; }
        public int getCustomerID() { return this.customerID; }
        public string getDate() { return this.date; }
        public double getPrice() { return this.price; }
        public List<Seat> getSeats() { return this.bookedSeats; }
    }
}
