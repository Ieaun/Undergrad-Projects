using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagementUI_Test
{
    /// <summary>
    /// Customer object to store information on a customer
    /// </summary>
    public class Customer
    {
        // Private Members
        private string mID;
        private string mFirstName;
        private string mLastName;
        private string mContactNumber;
        private bool isGold = false;
        private DateTime date;

        // Constructor to assign local members
        public Customer(string pID, string pFirstName, string pLastName, string pContactNumber)
        {
            this.setID(pID);
            this.setFirstName(pFirstName);
            this.setLastName(pLastName);
            this.setContactNumber(pContactNumber);
        }

        // Setters
        public void setID(string pID) { this.mID = pID; }
        public void setFirstName(string pFirstName) { this.mFirstName = pFirstName; }
        public void setLastName(string pLastName) { this.mLastName = pLastName; }
        public void setContactNumber(string pContactNumber) { this.mContactNumber = pContactNumber; }
        public void setIsGold(bool pIsGold) { this.isGold = pIsGold; }
        public void setDate(DateTime pDate) { this.date = pDate; }

        // Getters
        public string getID() { return this.mID; }
        public string getFirstName() { return this.mFirstName; }
        public string getLastName() { return this.mLastName; }
        public string getContactNumber() { return this.mContactNumber; }
        public bool getIsGold() { return this.isGold; }
        public DateTime getDate() { return this.date; }
    }
}
