using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagementUI_Test
{
    /// <summary>
    /// Seat object to store information about a specific seat
    /// </summary>
    public class Seat
    {
        // Private members
        private string area;
        private int rowIndex;
        private int seatIndex;
        private string status;

        // Constructor assigns local members
        public Seat(string pArea, int pRowIndex, int pSeatIndex, string pStatus)
        {
            this.area = pArea;
            this.rowIndex = pRowIndex;
            this.seatIndex = pSeatIndex;
            this.status = pStatus;
        }

        // Getters
        public string getArea() { return this.area; }
        public int getRowIndex() { return this.rowIndex; }
        public int getSeatIndex() { return this.seatIndex; }
        public string getStatus() { return this.status; }

    }
}
