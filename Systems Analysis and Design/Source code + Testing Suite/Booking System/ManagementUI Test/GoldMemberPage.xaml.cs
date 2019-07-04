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
    /// Interaction logic for GoldMemberPage.xaml
    /// </summary>
    public partial class GoldMemberPage : Window
    {
        // Variables
        List<Customer> cust = new List<Customer>();
        List<string> months = new List<string>();
        List<Customer> goldCustomer = new List<Customer>();

        public GoldMemberPage()
        {
            InitializeComponent();

            // Queries database to get lsit of gold customers
            
            goldCustomer = SQL.CustomerSQL.QueryGoldMembers();
            cust = SQL.CustomerSQL.QueryFromDB();
            // Adds months to combobox
            months.Add("Jan");
            months.Add("Feb");
            months.Add("Mar");
            months.Add("Apr");
            months.Add("May");
            months.Add("Jun");
            months.Add("Jul");
            months.Add("Aug");
            months.Add("Sep");
            months.Add("Oct");
            months.Add("Nov");
            months.Add("Dec");

            // Loops through lists adding items to listboxes
            
            for (int i = 0; i < months.Count; i++)
            {
                RenewlMonth.Items.Add(months[i]);
            }
            RenewlMonth.SelectedItem = months[0];

            foreach (Customer item in goldCustomer)
            {
                GoldCustomers_listbox.Items.Add(item.getFirstName() + " " + item.getLastName());
            }
            updateCustomers();
            
        }

        // Updates the customer list by querying the database and then looping
        // through the results adding them to the lsitbox
        private void updateCustomers() {
            cust = SQL.CustomerSQL.QueryFromDB();
            Customer_ListBox.Items.Clear();
            for (int i = 0; i < cust.Count; i++)
            {
                if (!cust[i].getIsGold())
                {
                    Customer_ListBox.Items.Add(cust[i].getFirstName() + " " + cust[i].getLastName());
                }
                else
                {
                    cust.Remove(cust[i]);
                    i--;
                }
            }
        }

        // Back button function, switches to the main window
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {

            MainWindow man = new MainWindow();
            this.Close();
            man.ShowDialog();
        }

        // Validation on text fields on page
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            // Validation
            bool addressIsText = AddressBox.Text.Any(x => char.IsLetter(x));
            bool cityTown = CityTownBox.Text.Any(x => char.IsLetter(x));
            bool postCode = PostCodeBox.Text.Any(x => char.IsLetter(x));
            bool noOneSelected = false;
            int index = Customer_ListBox.SelectedIndex;
            if (addressIsText == false)
            {
                MessageBox.Show("Address 1 Not Valid");
            }
            if (cityTown == false)
            {
                MessageBox.Show("Please enter a city or a town.");
            }
            if (postCode == false)
            {
                MessageBox.Show("Post Code is not valid.");
            }
            if (index == -1)
            {
                MessageBox.Show("Please Select a Customer");
                noOneSelected = true;
            }

            // Checks the validation results
            if (addressIsText == true && cityTown == true && postCode == true && noOneSelected == false)
            {
                
                transferUser(index);
            }
            // Updates customer list
            updateCustomers();

        }

        // Changes a customer into a gold member
        private void transferUser(int index)
        {
            // Updates the database
            SQL.CustomerSQL.UpdateCustomer(cust[index].getID().ToString(), AddressBox.Text, AddressBox2.Text, CityTownBox.Text, PostCodeBox.Text, DateTime.Now.ToString("dd/MM/yyyy"));
            //cust[index].setIsGold(true);
            
            // Updates the gold members list and listbox
            goldCustomer = SQL.CustomerSQL.QueryGoldMembers();
            GoldCustomers_listbox.Items.Clear();
            foreach (Customer item in goldCustomer)
            {
                GoldCustomers_listbox.Items.Add(item.getFirstName() +" "+ item.getLastName());
            }           
        }

        // Updates the list of members who need membership renewed when a month is selected
        private void RenewlMonth_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // Clears the lsitbox
            RenewelListBox.Items.Clear();
            int monthNum = RenewlMonth.SelectedIndex + 1;
            string joindate = "";
            // Loops through each customer and calculates whether their expiry date is the selected month
            for (int i = 0; i < goldCustomer.Count; i++)
            {
                 joindate = goldCustomer[i].getDate().ToString();
                char[] getMonthfromString = joindate.ToCharArray();
                int firstNum = int.Parse(getMonthfromString[3].ToString());
                int secondNum = int.Parse(getMonthfromString[4].ToString());
                string bothNums = firstNum.ToString() + secondNum.ToString();
                int endMonth = int.Parse(bothNums);
                // If their membership expires this month it adds them to the listbox
                if (endMonth == monthNum)
                {
                    RenewelListBox.Items.Add(goldCustomer[i].getFirstName() + " " + goldCustomer[i].getLastName());
                }
            }
        }
    }
}
