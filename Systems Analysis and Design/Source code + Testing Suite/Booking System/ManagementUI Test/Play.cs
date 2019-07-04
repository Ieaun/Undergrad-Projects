using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagementUI_Test
{
    public class Play
    {
        // Private Members
        private string mID;
        private string mName;
        private string mType;
        private double mStallPrice;
        private double mUpperPrice;
        private double mDressPrice;
        private double mLength;

        // Constructor assigns local members
        public Play(string pID, string pName, string pType, double pStallPrice, double pUpperPrice, double pDressPrice, double pLength)
        {
            this.setID(pID);
            this.setName(pName);
            this.setType(pType);
            this.setPrices(pStallPrice, pUpperPrice, pDressPrice);
            this.setLength(pLength);
        }

        // Setters
        public void setID(string pID) { this.mID = pID; }
        public void setName(string pName) { this.mName = pName; }
        public void setType(string pType) { this.mType = pType; }
        public void setLength(double pLength) { this.mLength = pLength; }
        public void setPrices(double pStallPrice, double pUpperPrice, double pDressPrice) {
            this.mStallPrice = pStallPrice;
            this.mUpperPrice = pUpperPrice;
            this.mDressPrice = pDressPrice;
        }

        // Getters 
        public string getID() { return this.mID; }
        public string getName() { return this.mName; }
        public string getType() { return this.mType; }
        public double getStallPrice() { return this.mStallPrice; }
        public double getUpperPrice() { return this.mUpperPrice; }
        public double getDressPrice() { return this.mDressPrice; }
        public double getLength() { return this.mLength; }
    }
}
