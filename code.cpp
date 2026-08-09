#include <iostream>
#include <string>

using namespace std;

string adminUsername = "admin";
string adminPassword = "1234";

int nextTicketID = 1001;
double totalRevenue = 0;
int normalTicketsBooked = 0;
int priorityTicketsBooked = 0;


struct Bus
{
    int busID;
    string routeNo;
    string stops[10];
    int totalStops;
    int currentStopIndex;
    int seats;
    int bookedSeats;
    string status;
};

Bus buses[5] =
{
    {101,"R1",{"Model Colony","Malir Halt","Drigh Road","Karsaz","Nursery","Tower"},6,0,40,0,"On Route"},
    {102,"R3",{"Power House","Nagan Chowrangi","Sakhi Hasan","KDA Chowrangi","Liaquatabad"},5,0,35,0,"On Route"},
    {103,"R2",{"New Karachi","Nagan Chowrangi","Shafiq Mor","Sohrab Goth","Gulshan","Nipa","Johar Mor","Korangi"},8,0,40,0,"On Route"},
    {104,"R10",{"Numaish","Korangi","Shah Faisal","Ibrahim Hyderi"},4,0,30,0,"On Route"},
    {105,"R9",{"Tower","Banaras","Orangi"},3,0,25,0,"On Route"}
};



struct Route
{
    int routeID;
    string routeName;
    string currentLocation;
    int seats;
    Route* left;
    Route* right;
};

Route* routeRoot = NULL;

Route* createRoute(int id, string name, string location, int seats)
{
    Route* temp = new Route;
    temp->routeID = id;
    temp->routeName = name;
    temp->currentLocation = location;
    temp->seats = seats;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

Route* insertRoute(Route* root, int id, string name, string location, int seats)
{
    if (root == NULL)
        return createRoute(id, name, location, seats);

    if (id < root->routeID)
        root->left = insertRoute(root->left, id, name, location, seats);
    else
        root->right = insertRoute(root->right, id, name, location, seats);

    return root;
}

Route* searchRoute(Route* root, int id)
{
    if (root == NULL) return NULL;
    if (root->routeID == id) return root;
    if (id < root->routeID) return searchRoute(root->left, id);
    return searchRoute(root->right, id);
}


struct Ticket
{
    int ticketID;
    string passengerName;
    string routeNo;
    int priority;
};

const int MAX = 100;

Ticket bookingQueue[MAX];
int front = -1;
int rear = -1;

Ticket heap[100];
int n = 0;

string locationStack[100];
int top = -1;

void printSlip(string passengerName, int ticketID,
    string routeNo, string routePath,
    double fare, string ticketType)
{
    cout << "\n";
    cout << "  ============================================\n";
    cout << "         KARACHI BUS SCHEDULING SYSTEM        \n";
    cout << "  ============================================\n";
    cout << "  Ticket Type : " << ticketType << "\n";
    cout << "  --------------------------------------------\n";
    cout << "  Ticket ID   : " << ticketID << "\n";
    cout << "  Passenger   : " << passengerName << "\n";
    cout << "  Route No    : " << routeNo << "\n";
    cout << "  Route Path  : " << routePath << "\n";
    cout << "  --------------------------------------------\n";
    cout << "  Fare        : Rs. " << fare << "\n";
    cout << "  ============================================\n";
    cout << "       Thank you for travelling with us!      \n";
    cout << "  ============================================\n\n";
}



void showAllRoutes()
{
    cout << "\n===== ALL ROUTES =====\n";

    for (int i = 0; i < 5; i++)
    {
        cout << "\nBus ID         : " << buses[i].busID;
        cout << "\nRoute No       : " << buses[i].routeNo;
        cout << "\nStatus         : " << buses[i].status;

        Route* r = searchRoute(routeRoot, buses[i].busID);

        if (r != NULL)
        {
            cout << "\nCurrent Location: "
                << r->currentLocation;
        }

        cout << "\nStops          : ";

        for (int j = 0; j < buses[i].totalStops; j++)
        {
            cout << buses[i].stops[j];

            if (j != buses[i].totalStops - 1)
                cout << " -> ";
        }

        cout << "\nTotal Seats    : " << buses[i].seats;
        cout << "\nBooked Seats   : " << buses[i].bookedSeats;
        cout << "\nAvailable Seats: "
            << buses[i].seats - buses[i].bookedSeats;

        cout << "\n--------------------------";
    }
}

void displayAvailableSeats()
{
    cout << "\n===== AVAILABLE SEATS =====\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "\nRoute: " << buses[i].routeNo;
        cout << "\nAvailable Seats: " << buses[i].seats - buses[i].bookedSeats;
        cout << "\n----------------";
    }
}


string buildRoutePath(int busIndex)
{
    string path = "";
    for (int j = 0; j < buses[busIndex].totalStops; j++)
    {
        path += buses[busIndex].stops[j];
        if (j != buses[busIndex].totalStops - 1)
            path += " -> ";
    }
    return path;
}


void showRoutesForBooking()
{
    cout << "\n  ==================== AVAILABLE ROUTES ====================\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "\n  Bus ID  : " << buses[i].busID;
        cout << "\n  Route   : " << buses[i].routeNo;
        cout << "\n  Status  : " << buses[i].status;
        cout << "\n  Stops   : ";
        for (int j = 0; j < buses[i].totalStops; j++)
        {
            cout << buses[i].stops[j];
            if (j != buses[i].totalStops - 1) cout << " -> ";
        }
        cout << "\n  Seats   : "
            << buses[i].seats - buses[i].bookedSeats
            << " available / " << buses[i].seats << " total";
        cout << "\n  ----------------------------------------------------------";
    }
    cout << "\n";
}

void bookTicket()
{
    if ((front == rear + 1) || (front == 0 && rear == MAX - 1))
    {
        cout << "\nQUEUE OVERFLOW\n";
        return;
    }

    Ticket t;
    t.ticketID = nextTicketID++;

    showRoutesForBooking();

    cin.ignore(1000, '\n');

    cout << "Enter Passenger Name: ";
    getline(cin, t.passengerName);

    cout << "Enter Route No      : ";
    cin >> t.routeNo;

    bool found = false;
    int foundIndex = -1;

    for (int i = 0; i < 5; i++)
    {
        if (buses[i].routeNo == t.routeNo)
        {
            found = true;
            foundIndex = i;

            if (buses[i].bookedSeats >= buses[i].seats)
            {
                cout << "\nNo Seats Available On This Route\n";
                return;
            }

            break;
        }
    }

    if (!found)
    {
        cout << "\nInvalid Route Number\n";
        return;
    }

    if (front == -1)
    {
        front = rear = 0;
    }
    else if (rear == MAX - 1)
    {
        rear = 0;
    }
    else
    {
        rear++;
    }

    bookingQueue[rear] = t;

    string path = buildRoutePath(foundIndex);

    cout << "\nTicket Request Added To Queue Successfully!\n";

    printSlip(
        t.passengerName,
        t.ticketID,
        t.routeNo,
        path,
        100.0,
        "Pending Normal Ticket"
    );
}
void showQueue()
{
    int i = front;

    while (true)
    {
        cout << "\nTicket ID : " << bookingQueue[i].ticketID;
        cout << "\nPassenger : " << bookingQueue[i].passengerName;
        cout << "\nRoute     : " << bookingQueue[i].routeNo;
        cout << "\n----------------";

        if (i == rear)
            break;

        if (i == MAX - 1)
            i = 0;
        else
            i++;
    }
}
void processBooking()
{
    if (front == -1)
    {
        cout << "\nNo Booking Available\n";
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        if (buses[i].routeNo == bookingQueue[front].routeNo)
        {
            if (buses[i].bookedSeats < buses[i].seats)
            {
                buses[i].bookedSeats++;

                totalRevenue += 100;
                normalTicketsBooked++;
            }
            else
            {
                cout << "\nNo Seats Available Now!\n";
                return;
            }

            break;
        }
    }

    cout << "\n===== BOOKING CONFIRMED =====";
    cout << "\nTicket ID : " << bookingQueue[front].ticketID;
    cout << "\nPassenger : " << bookingQueue[front].passengerName;
    cout << "\nRoute     : " << bookingQueue[front].routeNo;
    cout << "\nSeat Assigned Successfully\n";

    if (front == rear)
    {
        front = rear = -1;
    }
    else if (front == MAX - 1)
    {
        front = 0;
    }
    else
    {
        front++;
    }
}
void heapify(int i)
{
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= n && heap[left].priority > heap[largest].priority)
    {
        largest = left;
    }

    if (right <= n && heap[right].priority > heap[largest].priority)
    {
        largest = right;
    }

    if (largest != i)
    {
        Ticket temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        heapify(largest);
    }
}

void buildMaxHeap()
{
    for (int i = n / 2; i >= 1; i--)
        heapify(i);
}

void insertHeap()
{
    if (n == 99)
    {
        cout << "\nPriority Queue Full\n";
        return;
    }

    Ticket t;
    t.ticketID = nextTicketID++;

    showRoutesForBooking();

    cin.ignore();

    cout << "Enter Passenger Name: ";
    getline(cin, t.passengerName);

    cout << "Enter Route No      : ";
    cin >> t.routeNo;

    cout << "Enter Priority (1-10): ";
    cin >> t.priority;

    bool found = false;
    int foundIndex = -1;

    for (int i = 0; i < 5; i++)
    {
        if (buses[i].routeNo == t.routeNo)
        {
            found = true;
            foundIndex = i;

            if (buses[i].bookedSeats >= buses[i].seats)
            {
                cout << "\nNo Seats Available On This Route\n";
                return;
            }

            break;
        }
    }

    if (!found)
    {
        cout << "\nInvalid Route Number\n";
        return;
    }

    n++;
    heap[n] = t;

    buildMaxHeap();

    string path = buildRoutePath(foundIndex);

    cout << "\nPriority Ticket Request Added Successfully!\n";

    printSlip(t.passengerName, t.ticketID, t.routeNo, path, 150.0, "Pending Priority Ticket");
}
void showPriorityBookings()
{
    if (n == 0)
    {
        cout << "\nNo Priority Bookings\n";
        return;
    }

    cout << "\n===== PRIORITY BOOKINGS =====\n";
    for (int i = 1; i <= n; i++)
    {
        cout << "\nTicket ID : " << heap[i].ticketID;
        cout << "\nPassenger : " << heap[i].passengerName;
        cout << "\nRoute     : " << heap[i].routeNo;
        cout << "\nPriority  : " << heap[i].priority;
        cout << "\n----------------";
    }
}
void processPriorityBooking()
{
    if (n == 0)
    {
        cout << "\nNo Priority Booking Available\n";
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        if (buses[i].routeNo == heap[1].routeNo)
        {
            if (buses[i].bookedSeats < buses[i].seats)
            {
                buses[i].bookedSeats++;

                totalRevenue += 150;
                priorityTicketsBooked++;
            }
            else
            {
                cout << "\nNo Seats Available Now!\n";
                return;
            }

            break;
        }
    }

    cout << "\n===== PRIORITY BOOKING CONFIRMED =====";
    cout << "\nTicket ID : " << heap[1].ticketID;
    cout << "\nPassenger : " << heap[1].passengerName;
    cout << "\nRoute     : " << heap[1].routeNo;
    cout << "\nPriority  : " << heap[1].priority;
    cout << "\nSeat Assigned Successfully\n";

    heap[1] = heap[n];
    n--;

    buildMaxHeap();
}void updateLocation(Route* root)
{
    int id;
    cout << "\nValid Route IDs: 101(R1), 102(R3), 103(R2), 104(R10), 105(R9)";
    cout << "\nEnter Route ID: ";
    cin >> id;


    Route* r = searchRoute(root, id);

    if (r == NULL)
    {
        cout << "\nRoute Not Found\n";
        return;
    }

    if (top == 99)
    {
        cout << "\nLocation History Stack Full\n";
        return;
    }

    locationStack[++top] = r->currentLocation;

    cin.ignore();
    cout << "Enter New Location: ";
    getline(cin, r->currentLocation);

    cout << "\nLocation Updated Successfully\n";
}
void undoLocation(Route* root)
{
    int id;

    cout << "\nEnter Route ID: ";
    cin >> id;

    Route* r = searchRoute(root, id);

    if (r == NULL)
    {
        cout << "\nRoute Not Found\n";
        return;
    }

    if (top == -1)
    {
        cout << "\nNo Previous Location Available\n";
        return;
    }

    r->currentLocation = locationStack[top--];

    cout << "\nLocation Restored Successfully\n";
    cout << "Current Location: " << r->currentLocation << endl;
}
void searchRouteByID()
{
    int id;

    cout << "\nEnter Route ID: ";
    cin >> id;

    Route* r = searchRoute(routeRoot, id);

    if (r == NULL)
    {
        cout << "\nRoute Not Found\n";
        return;
    }

    cout << "\n===== ROUTE FOUND =====";
    cout << "\nRoute ID         : " << r->routeID;
    cout << "\nRoute Name       : " << r->routeName;
    cout << "\nCurrent Location : " << r->currentLocation;
    cout << "\nSeats            : " << r->seats;
    cout << endl;
}

void showRevenue()
{
    cout << "\n\n===== REVENUE REPORT =====";

    cout << "\nNormal Tickets Booked   : "
        << normalTicketsBooked;

    cout << "\nRevenue From Normal     : Rs. "
        << normalTicketsBooked * 100;

    cout << "\n\nPriority Tickets Booked : "
        << priorityTicketsBooked;

    cout << "\nRevenue From Priority   : Rs. "
        << priorityTicketsBooked * 150;

    cout << "\n\nTotal Tickets Booked    : "
        << normalTicketsBooked + priorityTicketsBooked;

    cout << "\nTotal Revenue Generated : Rs. "
        << totalRevenue;

    cout << "\n==============================\n";
}

void passengerPanel()
{
    int choice;

    do
    {
        cout << "\n\n===== PASSENGER PANEL =====";
        cout << "\n1. Book Ticket         (Rs. 100)";
        cout << "\n2. View Queue";
        cout << "\n3. Book Priority Ticket (Rs. 150)";
        cout << "\n4. View Priority Bookings";
        cout << "\n5. Show All Routes";
        cout << "\n0. Back";

        cout << "\nChoice: ";
        cin >> choice;

        if (choice == 1) bookTicket();
        else if (choice == 2) showQueue();
        else if (choice == 3) insertHeap();
        else if (choice == 4) showPriorityBookings();
        else if (choice == 5) showAllRoutes();

    } while (choice != 0);
}


bool adminLogin()
{
    string username, password;

    cout << "\n===== ADMIN LOGIN =====";
    cout << "\nUsername: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword)
    {
        cout << "\nLogin Successful!\n";
        return true;
    }

    cout << "\nInvalid Username or Password!\n";
    return false;
}


void adminPanel()
{
    int choice;
    do
    {
        cout << "\n\n===== ADMIN PANEL =====";
        cout << "\n1. Process Queue Booking";
        cout << "\n2. Process Priority Booking";
        cout << "\n3. Update Location";
        cout << "\n4. Undo Location Update";
        cout << "\n5. Search Route By ID";
        cout << "\n6. Show All Routes";
        cout << "\n7. Display Available Seats";
        cout << "\n8. Revenue Report";
        cout << "\n0. Back";

        cout << "\nChoice: ";
        cin >> choice;

        if (choice == 1) processBooking();
        else if (choice == 2) processPriorityBooking();
        else if (choice == 3) updateLocation(routeRoot);
        else if (choice == 4) undoLocation(routeRoot);
        else if (choice == 5) searchRouteByID();
        else if (choice == 6) showAllRoutes();
        else if (choice == 7) displayAvailableSeats();
        else if (choice == 8) showRevenue();

    } while (choice != 0);
}

int main()
{
    routeRoot = insertRoute(routeRoot, 101, "R1", "Model Colony", 40);
    routeRoot = insertRoute(routeRoot, 102, "R3", "Power House", 35);
    routeRoot = insertRoute(routeRoot, 103, "R2", "New Karachi", 40);
    routeRoot = insertRoute(routeRoot, 104, "R10", "Numaish", 30);
    routeRoot = insertRoute(routeRoot, 105, "R9", "Tower", 25);

    int choice;

    do
    {
        cout << "\n\n===== BUS SCHEDULING SYSTEM =====";
        cout << "\n1. Passenger Panel";
        cout << "\n2. Admin Panel";
        cout << "\n0. Exit";

        cout << "\nChoice: ";
        cin >> choice;

        if (choice == 1)
            passengerPanel();
        else if (choice == 2)
        {
            if (adminLogin())
                adminPanel();
        }

    } while (choice != 0);

    cout << "\nThank You For Using System\n";
    return 0;
}