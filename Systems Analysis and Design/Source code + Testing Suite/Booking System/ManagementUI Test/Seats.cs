using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagementUI_Test
{
    /// <summary>
    /// Seats object to store information on all the seats for a performance
    /// </summary>
    public class Seats
    {
        // Private members
        private List<List<string>> mStalls;
        private List<List<string>> mUpperCircle;
        private List<List<string>> mDressCircle;
        private int mStallSeats;
        private int mUpperSeats;
        private int mDressSeats;

        // Constructor initialises the seats
        public Seats()
        {
            this.setStalls();
            this.setUpperCircle();
            this.setDressCircle();
        }

        // Initialises stalls seats
        public void setStalls()
        {
            // This sets up each seat in stalls
            this.mStalls = new List<List<string>>(12);
            this.mStalls.Add(new List<string>(17));
            this.mStalls.Add(new List<string>(16));
            this.mStalls.Add(new List<string>(20));
            this.mStalls.Add(new List<string>(22));
            this.mStalls.Add(new List<string>(22));
            this.mStalls.Add(new List<string>(21));
            this.mStalls.Add(new List<string>(22));
            this.mStalls.Add(new List<string>(22));
            this.mStalls.Add(new List<string>(22));
            this.mStalls.Add(new List<string>(20));
            this.mStalls.Add(new List<string>(20));
            this.mStalls.Add(new List<string>(16));
        }
        // Initialises upper seats
        public void setUpperCircle()
        {
            this.mUpperCircle = new List<List<string>>(5);
            this.mUpperCircle.Add(new List<string>(22));
            this.mUpperCircle.Add(new List<string>(25));
            this.mUpperCircle.Add(new List<string>(25));
            this.mUpperCircle.Add(new List<string>(25));
            this.mUpperCircle.Add(new List<string>(10));
        }

        // Initialises Dress seats
        public void setDressCircle()
        {
            this.mDressCircle = new List<List<string>>(5);
            this.mDressCircle.Add(new List<string>(35));
            this.mDressCircle.Add(new List<string>(37));
            this.mDressCircle.Add(new List<string>(19));
            this.mDressCircle.Add(new List<string>(23));
            this.mDressCircle.Add(new List<string>(23));
        }


        /// <summary>
        /// Sets a seat to booked
        /// </summary>
        /// <param name="area"></param> Area which seat is located
        /// <param name="rowIndex"></param> Row index of seat
        /// <param name="seatIndex"></param> Index of seat
        /// <returns>
        /// Returns bool value to check whether it was added successfully
        /// </returns>
        public bool bookSeat(string area, int rowIndex, int seatIndex) {
            // Stores whether or not the seat has been booked, only changed if it has
            bool status = false;

            // Checks the area
            switch (area) {
                case "Stalls":
                    // Checks whether seat is empty
                    if (this.mStalls[rowIndex][seatIndex].Equals("empty"))
                    {
                        this.mStalls[rowIndex][seatIndex] = "booked";
                        status = true;
                    }
                    break;
                case "Upper Circle":
                    // Checks whether seat is empty
                    if (this.mUpperCircle[rowIndex][seatIndex].Equals("empty"))
                    {
                        this.mUpperCircle[rowIndex][seatIndex] = "booked";
                        status = true;
                    }
                    break;
                case "Dress Circle":
                    // Checks whether seat is empty
                    if (this.mDressCircle[rowIndex][seatIndex].Equals("empty"))
                    {
                        this.mDressCircle[rowIndex][seatIndex] = "booked";
                        status = true;
                    }
                    break;
            }
            return status;
        }

        /// <summary>
        /// Sets a seat to empty
        /// </summary>
        /// <param name="seat"></param> Seat object to store its position and status
        public void unbookSeat(Seat seat) {
            // Checks the area and then sets the seat to empty
            switch (seat.getArea())
            {
                case "Stalls":
                    this.mStalls[seat.getRowIndex()][seat.getSeatIndex()] = "empty";
                    break;
                case "Upper Circle":
                    this.mUpperCircle[seat.getRowIndex()][seat.getSeatIndex()] = "empty";
                    break;
                case "Dress Circle":
                    this.mDressCircle[seat.getRowIndex()][seat.getSeatIndex()] = "empty";
                    break;
            }
        }

        /// <summary>
        /// Gets the status of a specific seat
        /// </summary>
        /// <param name="area"></param> Area which seat is located
        /// <param name="rowIndex"></param> Row index of seat
        /// <param name="seatIndex"></param> Seat index of seat
        /// <returns>
        /// Returns string value of specified seat
        /// </returns>
        public string getSeatAt(string area, int rowIndex, int seatIndex) {
            // Seat value, changed if seat is booked
            string seat = "empty";
            // Checks the area
            switch (area)
            {
                case "Stalls":
                    seat = this.mStalls[rowIndex][seatIndex];
                    break;
                case "Upper Circle":
                    seat = this.mUpperCircle[rowIndex][seatIndex];
                    break;
                case "Dress Circle":
                    seat = this.mDressCircle[rowIndex][seatIndex];
                    break;
            }
            return seat;
        }

        // Returns how many seats in the stalls are empty
        public int getSeatsLeftStall()
        {
            // Loops through each row and then seat counting the total
            this.mStallSeats = 0;
            foreach (List<string> row in this.mStalls)
            {
                foreach (string seat in row)
                {
                    // Only counts the seat if it is marked as empty
                    if (seat.ToLower().Equals("empty"))
                    {
                        this.mStallSeats++;
                    }
                }
            }
            return this.mStallSeats;
        }

        // Returns how many seats in the upper circle are empty
        public int getSeatsLeftUpper()
        {
            // Loops through each row and then seat counting the total
            this.mUpperSeats = 0;
            foreach (List<string> row in this.mUpperCircle)
            {
                foreach (string seat in row)
                {
                    // Only counts the seat if it is marked as empty
                    if (seat.ToLower().Equals("empty"))
                    {
                        this.mUpperSeats++;
                    }
                }
            }
            return this.mUpperSeats;
        }

        // Returns how many seats in the dress circle are empty
        public int getSeatsLeftDress()
        {
            // Loops through each row and then seat counting the total
            this.mDressSeats = 0;
            foreach (List<string> row in this.mDressCircle)
            {
                foreach (string seat in row)
                {
                    // Only counts the seat if it is marked as empty
                    if (seat.ToLower().Equals("empty"))
                    {
                        this.mDressSeats++;
                    }
                }
            }
            return this.mUpperSeats;
        }

        /// <summary>
        /// Used to convert lists of seats into Seats data structure
        /// </summary>
        /// <param name="stallList"></param> List of all seats in stalls without rows
        /// <param name="upperList"></param> List of all seats in upper circle without rows
        /// <param name="dressList"></param> List of all seats in dress circle without rows
        internal void populate(List<string> stallList, List<string> upperList, List<string> dressList)
        {
            // Loops through using count and capcity values to set up rows
            int counter = 0;
            for (int i = 0; i < this.mStalls.Count; i++)
            {

                for (int b = 0; b < this.mStalls[i].Capacity; b++)
                {
                    this.mStalls[i].Add(stallList[counter]);
                    counter++;
                }
            }

            // Loops through using count and capcity values to set up rows
            counter = 0;
            for (int i = 0; i < this.mUpperCircle.Count; i++)
            {

                for (int b = 0; b < this.mUpperCircle[i].Capacity; b++)
                {
                    this.mUpperCircle[i].Add(upperList[counter]);
                    counter++;
                }
            }

            // Loops through using count and capcity values to set up rows
            counter = 0;
            for (int i = 0; i < this.mDressCircle.Count; i++)
            {

                for (int b = 0; b < this.mDressCircle[i].Capacity; b++)
                {
                    this.mDressCircle[i].Add(dressList[counter]);
                    counter++;
                }
            }
        }

        

        // Returns how many seats are empty in the theatre
        public int getEmpty() { return (this.getSeatsLeftDress() + this.getSeatsLeftStall() + this.getSeatsLeftUpper()); }

        // Used to set all seats to empty
        public void setSeatsEmpty()
        {

            // Loops through setting each seat to empty
            for (int i = 0; i < this.mStalls.Count; i++)
            {

                for (int b = 0; b < this.mStalls[i].Capacity; b++)
                {
                    this.mStalls[i].Add("empty");
                }
            }

            // Loops through setting each seat to empty
            for (int i = 0; i < this.mUpperCircle.Count; i++)
            {
                for (int b = 0; b < this.mUpperCircle[i].Capacity; b++)
                {
                    this.mUpperCircle[i].Add("empty");
                }
            }

            // Loops through setting each seat to empty
            for (int i = 0; i < this.mDressCircle.Count; i++)
            {
                for (int b = 0; b < this.mDressCircle[i].Capacity; b++)
                {
                    this.mDressCircle[i].Add("empty");
                }
            }
        }

        // Get methods to return the list of seats
        public List<List<string>> getStalls() { return this.mStalls; }
        public List<List<string>> getUpperSeats() { return this.mUpperCircle; }
        public List<List<string>> getDressSeats() { return this.mDressCircle; }

        /// <summary>
        /// Gets the specified row
        /// </summary>
        /// <param name="area"></param> Area in which row is
        /// <param name="index"></param> Index of the row
        /// <returns>
        /// Returns the row as a list of seats
        /// </returns>
        public List<string> ReturnRow(string area,int index)
        {
            // Initialises row
            List<string> row = new List<string>();

            // Checks the area and then assigns the row
            switch (area) {
                case "Stalls":
                    row = this.mStalls[index];
                    break;
                case "Upper Circle":
                    row = this.mUpperCircle[index];
                    break;
                case "Dress Circle":
                    row = this.mDressCircle[index];
                    break;
            }
            return row; // Returns row
        }
    }
}