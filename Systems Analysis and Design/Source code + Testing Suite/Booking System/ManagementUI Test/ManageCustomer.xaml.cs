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
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {

        // Variables
        List<Customer> customerList = new List<Customer>();
        MainWindow main = new MainWindow();


        public void setMain(MainWindow pMain)
        {
            main = pMain;
        }

        // Constructor for window
        public Window1()
        {
            InitializeComponent();

            // Updates the list
            updateCustomerList();
        }

        // Deletes the currently selected customer from the database
        private void deleteSelectedCustomer_Click(object sender, RoutedEventArgs e)
        {
            // Gets the index of the selected customer
            if (CustomerListBox.SelectedIndex == -1)
            {
                return;
            }
            int customerIndex = CustomerListBox.SelectedIndex; // Gets the selected customer index
            Customer customerToDelete = customerList[customerIndex]; // Gets the customer from the list

            CustomerListBox.Items.RemoveAt(CustomerListBox.Items.IndexOf(CustomerListBox.SelectedItem)); // Removes customer from the listbox

            // Deletes the customer from the database
            SQL.CustomerSQL.DeleteFromDB(customerToDelete);


            // Then updates the list
            updateCustomerList();
        }

        // Uses information in text fields to add a new customer to the system
        private void createCustomer_Click(object sender, RoutedEventArgs e)
        {
            // Error checking
            if (cusFirstNameTextbox.Text.Equals("")){
                MessageBox.Show("You must enter a valid name.");
                return;
            }
            if (cusSurnameTextbox.Text.Equals("")) {
                MessageBox.Show("You must enter a valid Last name.");
                return;
            }
            if (customerContactTextbox.Text.Equals("")) {
                MessageBox.Show("The contact number cannot be blank.");
                return;
            }
            if (customerContactTextbox.Text.Length != 11) {
                MessageBox.Show("The contact number must be 11 digits.");
                return;
            }
            try
            {
                double.Parse(customerContactTextbox.Text);
            }
            catch (Exception) {
                MessageBox.Show("The contact number must be a valid number.");
                return;
            }

            // Creates a new Customer Object
            Customer newCustomer = new Customer("0", cusFirstNameTextbox.Text, cusSurnameTextbox.Text, customerContactTextbox.Text);

            // Adds it to the database
            SQL.CustomerSQL.AddToDB(newCustomer);

            // Then updates list 
            updateCustomerList();

            // Resests fields
            cusFirstNameTextbox.Text = "";
            cusSurnameTextbox.Text = "";
            customerContactTextbox.Text = "";
        }

        // Updates list of customers to window
        private void updateCustomerList()
        {
            // Updates the list of customers from the database
            customerList = SQL.CustomerSQL.QueryFromDB();

            CustomerListBox.Items.Clear();
            // Loops through the list adding them to the list box
            foreach (Customer customer in customerList) {
                CustomerListBox.Items.Add(customer.getFirstName() + " " + customer.getLastName());
            }
        }

        // Returns to the main window
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mn = new MainWindow();
            this.Close();
            mn.ShowDialog();   
        }
    }
}
