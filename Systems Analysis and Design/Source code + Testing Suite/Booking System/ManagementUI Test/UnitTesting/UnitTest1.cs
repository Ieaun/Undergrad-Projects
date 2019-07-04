using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using ManagementUI_Test;
using ManagementUI_Test.SQL;
using System.Collections.Generic;
using System.IO;

namespace UnitTesting
{
    [TestClass]
    public class UnitTest1
    {


        [TestMethod]
        public void CreateDatabase()
        {
            if(File.Exists("Database.sqlite"))
                File.Delete("Database.sqlite");
            CreateSQL.CreateDatabase();
            Assert.IsTrue(File.Exists("Database.sqlite"));
        }

        [TestMethod]
        public void AddCustomer()
        {
            string id = "1";
            string firstName = "Bob";
            string lastName = "Jones";
            string contactNumber = "074230903242";
            Customer customer = new Customer(id, firstName, lastName, contactNumber);
            CustomerSQL.AddToDB(customer);
            List<Customer> list = CustomerSQL.QueryFromDB();
            foreach (Customer customerInList in list) {
                Assert.AreEqual(firstName, customerInList.getFirstName());
            }
        }

        [TestMethod]
        public void DeleteCustomer() {
            string id = "1";
            string firstName = "Bob";
            string lastName = "Jones";
            string contactNumber = "074230903242";
            Customer customer = new Customer(id, firstName, lastName, contactNumber);
            CustomerSQL.DeleteFromDB(customer);
            List<Customer> list = CustomerSQL.QueryFromDB();
            Assert.AreEqual(0, list.Count);
            AddCustomer();
        }

        [TestMethod]
        public void QueryCustomers() {
            List<Customer> customerList = CustomerSQL.QueryFromDB();
            Assert.AreEqual(1, customerList.Count);
        }

        [TestMethod]
        public void QueryGoldMembers()
        {
            List<Customer> goldCustomerList = CustomerSQL.QueryGoldMembers();
            Assert.AreEqual(0, goldCustomerList.Count);
        }

        [TestMethod]
        public void UpdateCustomer() {
            string id = "1";
            string addressLine1 = "23 Winston Street";
            string addressLine2 = "Little Bealings";
            string city = "Narnia";
            string postcode = "NA2 2YT";
            string date = DateTime.Now.ToShortDateString();
            CustomerSQL.UpdateCustomer(id, addressLine1, addressLine2, city, postcode, date);
            List<Customer> goldCustomerList = CustomerSQL.QueryGoldMembers();
            Assert.AreEqual(0, goldCustomerList.Count);
        }

        [TestMethod]
        public void AddPlay() {
            string id = "1";
            string playName = "Peter Pan - The sequel";
            string type = "Main Play";
            double stallsPrice = 30.0;
            double upperPrice = 50.0;
            double dressPrice = 75.0;
            double length = 4.5;
            Play play = new Play(id, playName, type, stallsPrice, upperPrice, dressPrice, length);
            PlaySQL.AddToDB(play);
            List<Play> playsList = PlaySQL.QueryFromDB();
            Assert.AreEqual(1, playsList.Count);
        }

        [TestMethod]
        public void DeletePlay() {
            string id = "1";
            string playName = "Peter Pan - The Sequel";
            string type = "Main Play";
            double stallsPrice = 30.0;
            double upperPrice = 50.0;
            double dressPrice = 75.0;
            double length = 4.5;
            Play play = new Play(id, playName, type, stallsPrice, upperPrice, dressPrice, length);
            PlaySQL.DeleteFromDB(play);
            List<Play> playsList = PlaySQL.QueryFromDB();
            Assert.AreEqual(0, playsList.Count);
            AddPlay();
        }

        [TestMethod]
        public void QueryPlays() {
            List<Play> playsList = PlaySQL.QueryFromDB();
            Assert.AreEqual(1, playsList.Count);
        }

        [TestMethod]
        public void QueryPlayID() {
            string name = "Peter Pan - The Sequel";
            string id = PlaySQL.QueryID(name);
            Assert.AreNotEqual("1", id);
        }

        [TestMethod]
        public void AddPerformance() {
            string id = "1";
            string playName = "Peter Pan - The Sequel";
            string date = DateTime.Now.ToShortDateString();
            Performance performance = new Performance(id, playName, date);
            PerformanceSQL.AddToDB(performance);
            List<Performance> list = PerformanceSQL.QueryFromDB(id);
            Assert.AreEqual(0, list.Count);
        }

        [TestMethod]
        public void DeletePerformance() {
            string id = "1";
            string playName = "Peter Pan - The Sequel";
            string date = DateTime.Now.ToShortDateString();
            Performance performance = new Performance(id, playName, date);
            PerformanceSQL.DeleteFromDB(performance);
            List<Performance> list = PerformanceSQL.QueryFromDB(id);
            Assert.AreEqual(0, list.Count);
            AddPerformance();
        }

        [TestMethod]
        public void QueryPerformances()
        {
            string id = "2";
            List<Performance> performanceList = PerformanceSQL.QueryFromDB(id);
            Assert.AreEqual(0, performanceList.Count);
        }

        [TestMethod]
        public void QueryPerformanceID()
        {
            string date = DateTime.Now.ToShortDateString();
            string id = PerformanceSQL.QueryID(date);
            Assert.AreEqual("2", id);
        }

        [TestMethod]
        public void AddBooking() {
            bool result;
            double price = 100.0;
            string id = "0";
            string firstName = "Bob";
            string lastName = "Jones";
            string contactNumber = "074230903242";
            Customer customer = new Customer(id, firstName, lastName, contactNumber);
            List<Seat> bookedSeats = new List<Seat>();
            Seat seat = new Seat("Stalls", 0, 0, "booked");
            bookedSeats.Add(seat);
            result = BookingSQL.AddToDB(customer, id, bookedSeats, price);
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void DeleteBooking() {
            double price = 100.0;
            int id = 1;
            string firstName = "Bob";
            string lastName = "Jones";
            string contactNumber = "074230903242";
            string date = DateTime.Now.ToShortDateString();
            Customer customer = new Customer(id.ToString(), firstName, lastName, contactNumber);
            List<Seat> bookedSeats = new List<Seat>();
            Seat seat = new Seat("Stalls", 0, 0, "booked");
            bookedSeats.Add(seat);
            Booking booking = new Booking(id, id, int.Parse(customer.getID()), date, price);
            BookingSQL.DeleteFromDB(booking);
            List<Booking> bookingList;
            bookingList = BookingSQL.QueryFromDB();
            Assert.AreEqual(0, bookingList.Count);
        }

        [TestMethod]
        public void QueryBookings() {
            List<Booking> bookingList;
            bookingList = BookingSQL.QueryFromDB();
            Assert.AreEqual(0, bookingList.Count);
        }
    }
}
