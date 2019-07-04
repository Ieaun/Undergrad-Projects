using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagementUI_Test
{
    /// <summary>
    /// Performance object to store information about a specific Performance
    /// </summary>
    public class Performance
    {
        // Local members
        public Seats mSeats;
        private string mID;
        private string mPlayID;
        private string mDate;

        // Constructor assigns local members
        public Performance(string pID, string pPlayID, string pDate)
        {
            this.setID(pID);
            this.setPlay(pPlayID);
            this.setDate(pDate);
            this.setSeats();

        }

        // Setters
        public void setID(string pID) { this.mID = pID; }
        public void setPlay(string pPlayID) { this.mPlayID = pPlayID; }
        public void setDate(string pDate) { this.mDate = pDate; }
        public void setSeats() { this.mSeats = new Seats(); }

        // Getters
        public string getID() { return this.mID; }
        public string getPlay() { return this.mPlayID; }
        public string getDate() { return this.mDate; }
        public Seats getSeats() { return this.mSeats; }
    }
}
