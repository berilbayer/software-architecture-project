#include <iostream>
#include <list>
#include <vector>
#include <string.h>

using namespace std;

class Item{
private:
    string item_name;
    string item_description;
    float item_weight;
public:
    //every item has name,description and weight and they will not change. So I didn't use any mutators for this class.
    Item(string name, string description, float weight){
    item_name = name;
    item_description = description;
    item_weight = weight;
    }
    string getItemName(){
    return item_name;
    }
    string getItemDescription(){
    return item_description;
    }
    float getItemWeight(){
    return item_weight;
    }
};

class Doors{
private:
    //door can be either locked or unlocked. locked = false, unlocked = true.
    bool door_state;
public:
    Doors(bool initial_state){
    door_state = initial_state;
    }
    bool getDoorState(){
    return door_state;
    }
    void setDoorState(bool new_state){
    door_state = new_state;
    }
};

class Room{
private:
    string room_name;
    string room_description;
    Doors * door_to_south;
    Doors * door_to_north;
    Doors * door_to_east;
    Doors * door_to_west;
    Room * extends_to_south;
    Room * extends_to_north;
    Room * extends_to_east;
    Room * extends_to_west;
    vector<Item *> room_inventory;
public:
    Room(string name, string description){
    room_name = name;
    room_description = description;
    }
    void setDoors(Doors * dsouth, Doors * dnorth, Doors * deast, Doors * dwest){
    door_to_south = dsouth;
    door_to_north = dnorth;
    door_to_east = deast;
    door_to_west = dwest;
    }
    void setRoomInventory(Item * newItem){
    room_inventory.push_back(newItem);
    }
    // I could have merge these 4 set functions in one, my bad.
    void setExtendToSouth(Room * rsouth){
    extends_to_south = rsouth;
    }
    void setExtendToNorth(Room * rnorth){
    extends_to_north = rnorth;
    }
    void setExtendToEast(Room * reast){
    extends_to_east = reast;
    }
    void setExtendToWest(Room * rwest){
    extends_to_west = rwest;
    }
    string getRoomName(){
    return room_name;
    }
    string getRoomDescription(){
    return room_description;
    }
    Doors * getDoorToSouth(){
    return door_to_south;
    }
    Doors * getDoorToNorth(){
    return door_to_north;
    }
    Doors * getDoorToEast(){
    return door_to_east;
    }
    Doors * getDoorToWest(){
    return door_to_west;
    }
    Room * getRoomToSouth(){
    return extends_to_south;
    }
    Room * getRoomToNorth(){
    return extends_to_north;
    }
    Room * getRoomToEast(){
    return extends_to_east;
    }
    Room * getRoomToWest(){
    return extends_to_west;
    }

    void info(){
    cout<<this->getRoomName()<<endl;
    cout<<this->getRoomDescription()<<endl;
    cout<<"You are here. It extends to:"<<endl;
    if(this->getRoomToSouth() != NULL){
        cout<<"SOUTH"<<endl;
    }
    if(this->getRoomToNorth() != NULL){
        cout<<"NORTH"<<endl;
    }
    if(this->getRoomToEast() != NULL){
        cout<<"EAST"<<endl;
    }
    if(this->getRoomToWest() != NULL){
        cout<<"WEST"<<endl;
    }
    cout<<"Possible doors: "<<endl;
    if(this->getDoorToSouth() != NULL){
        cout<<"SOUTH DOOR"<<endl;
    }
    if(this->getDoorToNorth() != NULL){
        cout<<"NORTH DOOR"<<endl;
    }
    if(this->getDoorToEast() != NULL){
        cout<<"EAST DOOR"<<endl;
    }
    if(this->getDoorToWest() != NULL){
        cout<<"WEST DOOR"<<endl;
    }
    if(room_inventory.size() != 0){
       cout<<"Items: "<<endl;
       //for listing room inventory. I first try to use list, it didn't work then I used vector type. Thanks to stackoverflow
    for(int i = 0 ; i<room_inventory.size(); i++){
        cout<<room_inventory[i]->getItemName();
        cout<<" / "<<room_inventory[i]->getItemDescription()<<" / "<< room_inventory[i]->getItemWeight()<<" grams"<<endl;

    }}
    }
    bool getDoorToSouthState(){
    return door_to_south->getDoorState();
    }
    bool getDoorToNorthState(){
    return door_to_north->getDoorState();
    }
    bool getDoorToEastState(){
    return door_to_east->getDoorState();
    }
    bool getDoorToWestState(){
    return door_to_west->getDoorState();
    }
    void setDoorToEastState(bool state){
    door_to_east->setDoorState(state);
    }
};

class Character{
private:
    string character_name;
    string character_description;
    Room * currentRoom;
    vector<Item *> character_inventory;
    static Character * unique_instance;
    //constructor is private. for the sake of singleton pattern!
    Character(string name, string description, Room * initialRoom){
    character_name = name;
    character_description = description;
    currentRoom = initialRoom;
    }

public:
     static Character * createInstance(string n, string d, Room * r){
    if(unique_instance == NULL)
        unique_instance = new Character(n,d,r);
    return unique_instance;
    }
    void setCharacterInventory(Item * someItem){
    character_inventory.push_back(someItem);
    }
    float getTotalWeight(){
       float totalWeight = 0;
    for(int i= 0;i<character_inventory.size();i++){
        totalWeight = character_inventory[i]->getItemWeight() + totalWeight;}
        cout<<totalWeight;
    return totalWeight;
    }
    void takeItem(Item * newItem){
        float totalWeight = this->getTotalWeight();
    for(int i= 0;i<character_inventory.size();i++){
        totalWeight = character_inventory[i]->getItemWeight() + totalWeight;
    }
    totalWeight=totalWeight+ newItem->getItemWeight();
    if(totalWeight>2000.00){
       cout<<"You cannot take the "<<newItem->getItemName()<<". Your inventory cannot carry that much."<<endl;
    }
    else{
        character_inventory.push_back(newItem);
        cout<<"You take the "<<newItem->getItemName()<<endl;
             }
    }
    void moveDirection(string direction){
    if(direction == "SOUTH" && currentRoom->getRoomToSouth() != NULL){
            if(currentRoom->getDoorToSouth() == NULL){
                currentRoom = currentRoom->getRoomToSouth();
            }
            else if(currentRoom->getDoorToSouth() != NULL && currentRoom->getDoorToSouthState() != false){
                currentRoom = currentRoom->getRoomToSouth();
            }

            else if(currentRoom->getDoorToSouth() != NULL && currentRoom->getDoorToSouthState() == false){
                cout<<"This door is locked. You need a key to open it."<<endl;
            }

    }
    else if(direction == "SOUTH" && currentRoom->getRoomToSouth() == NULL){
        cout<<"You cannot go in that direction. No room or corridor there..."<<endl;
    }
     if(direction == "NORTH" && currentRoom->getRoomToNorth() != NULL){
            if(currentRoom->getDoorToNorth() == NULL){
                currentRoom = currentRoom->getRoomToNorth();
            }
            else if(currentRoom->getDoorToNorth() != NULL && currentRoom->getDoorToNorthState() != false){
                currentRoom = currentRoom->getRoomToNorth();
            }

            else if(currentRoom->getDoorToNorth() != NULL && currentRoom->getDoorToNorthState() == false){
                cout<<"This door is locked. You need a key to open it."<<endl;
            }

    }
    else if(direction == "NORTH" && currentRoom->getRoomToNorth() == NULL){
        cout<<"You cannot go in that direction. No room or corridor there..."<<endl;
    }

     if(direction == "EAST" && currentRoom->getRoomToEast() != NULL){
            if(currentRoom->getDoorToEast() == NULL){
                currentRoom = currentRoom->getRoomToEast();
            }
            else if(currentRoom->getDoorToEast() != NULL && currentRoom->getDoorToEastState() != false){
                currentRoom = currentRoom->getRoomToEast();
            }

            else if(currentRoom->getDoorToEast() != NULL && currentRoom->getDoorToEastState() == false){
                cout<<"This door is locked. You need a key to open it."<<endl;
            }

    }
    else if(direction == "EAST" && currentRoom->getRoomToEast() == NULL){
        cout<<"You cannot go in that direction. No room or corridor there..."<<endl;
    }

    if(direction == "WEST" && currentRoom->getRoomToWest() != NULL){
            if(currentRoom->getDoorToWest() == NULL){
                currentRoom = currentRoom->getRoomToWest();
            }
            else if(currentRoom->getDoorToWest() != NULL && currentRoom->getDoorToWestState() != false){
                currentRoom = currentRoom->getRoomToWest();
            }

            else if(currentRoom->getDoorToWest() != NULL && currentRoom->getDoorToWestState() == false){
                cout<<"This door is locked. You need a key to open it."<<endl;
            }

    }
    else if(direction == "WEST" && currentRoom->getRoomToWest() == NULL){
        cout<<"You cannot go in that direction. No room or corridor there..."<<endl;
    }
    }
    void info(){
    currentRoom->info();
    }
    Room * getCurrentRoom(){
    return currentRoom;
    }
};
Character * Character::unique_instance = NULL;


class OpenCommands{
public:
    virtual void openSouth() = 0;
    virtual void openNorth() = 0;
    virtual void openEast() = 0;
    virtual void openWest() = 0;
};
class openSouthCommand: public OpenCommands{
private:
    Character * commander;
public:
    void setCharacterForCommand(Character * c){
    commander = c;
    }
    void openSouth(){
         cout<<"The door opens."<<endl;
         commander->moveDirection("SOUTH");
    }

    void openNorth(){}
    void openEast(){}
    void openWest(){}


};

class openNorthCommand :public OpenCommands{
private:
    Character * commander;
public:
    void setCharacterForCommand(Character * c){
    commander = c;
    }
    void openNorth(){
    cout<<"The door opens."<<endl;
    commander->moveDirection("NORTH");
    }
     void openSouth(){}
     void openEast(){}
     void openWest(){}

};

class openEastCommand :public OpenCommands{
private:
    Character * commander;
public:
    void setCharacterForCommand(Character * c){
    commander = c;
    }
     void openEast(){
    cout<<"The door opens."<<endl;
    commander->moveDirection("EAST");
    }
     void openSouth(){}
     void openNorth(){}
     void openWest(){}

};

class openWestCommand: public OpenCommands{
private:
    Character * commander;
public:
    void setCharacterForCommand(Character * c){
    commander = c;
    }
    void openWest(){
    cout<<"The door opens."<<endl;
    commander->moveDirection("WEST");
    }
     void openSouth(){}
     void openNorth(){}
     void openEast(){}

};

class UseCommands{
    Character * commander;
    Room * currRoom;
public:
    void setCommander(Character * c){
    commander = c;
    }
    void setCurrentRoom(Room * current){
    currRoom =current;
    }
    void readLetter10(){
    cout<<"The paper reads: "<<endl;
    cout<<"Thank you Mario, but our rincess is in another castle!"<<endl;
    }
    void readLetter11(){
    cout<<"The paper reads: "<<endl;
    cout<<"All your base belong to us."<<endl;
    }
    void broomUse(){
    cout<<"You have cleaned this room."<<endl;
    }
    void IronKeyUse(){
      if(currRoom->getDoorToEastState() == false){
        currRoom->setDoorToEastState(true);
        commander->moveDirection("EAST");
      }


       }
};

int main(void){
//initializing rooms and corridors
   Room * c1 = new Room("Corridor","A corridor that extends to east. There is a door to the south. It looks unlocked. There is a sword and a shield on the floor.");
   Room * c2 = new Room("Corridor","A corridor that extends to east and west. The floor is wet.");
   Room * c3 = new Room("Corridor","A corridor that extends to east and west. The floor is wet. It smells like blood. There is a door to the south. It looks unlocked. ");
   Room * c4= new Room("Corridor","A corridor that extends to east and west. There is nothing here.");
   Room * c5 = new Room("Corridor","A corridor that extends to east and west. There is wooden door to the south. It looks unlocked. There is a paper on the floor.");
   Room * c6 = new Room("Corridor","A corridor that extends to east and west. There is nothing here");
   Room * c7 = new Room("Corridor","A corridor that extends to west. There is a door to south.");
   Room * c8 = new Room("Corridor","A corridor that extends to east and west. There are doors to west and south. Fresh air flows from south.");
   Room * c9 = new Room("Corridor","A corridor that extends to east and west. There is a door to south. Fresh air flows from south.");
   Room * c10 = new Room("Corridor","A corridor that extends to east and west. There is a door to the west.");
   Room * c11 = new Room("Corridor","A corridor that extends to east. It is a dead end. The air is stiff.");
   Room * c12 = new Room("Corridor","A corridor that extends to east. Fresh air comes from east.");
   Room * c13 = new Room("Corridor","A corridor that extends to east. Fresh air comes from east. There is a paper on the floor.");
   Room * c14 = new Room("Corridor","A corridor that extends to east. Fresh air comes from east. There is a door to east.");
   Room * c15 = new Room("Corridor","A corridor that extends to east. Fresh air comes from east. There is a door to east. It looks locked. Its lock is shaped like a diamond. You think of aggregation and composition. The thought quickly fades away.");
   Room * r1 = new Room("Kitchen","This is beautiful kitchen. However there is nothing useful. There are doors to south and east. The door to the south smells good, maybe there is food in there.");
   Room * r2 = new Room("Storage","This is a simple storage. There are many things in here.");
   Room * r3 = new Room("Cellar","There is all kinds of food here. The pizza boxes catch your attention. However, it is not time for eating.");
   Room * r4 = new Room("Bedroom","This is a bedroom. There is dead man on the bed. His blood leaked from the bed to the floor. The scene is horrible, and you want to get out immediately. You see a text on one of the walls: DIE SHELDON DIE!");
   Room * r5 = new Room("Undefined","Undefined");
   Room * r6 = new Room("Living Room","There is table and four chairs in this room. There are doors to north and south.");
   Room * r7 = new Room("Treasure Room","This room has a very large open window. A powerful wind carries fresh air. The floor is full of gold coins.");
   Room * r8 = new Room("Dinner Room","This looks like a dinner room. There are doors to north and east.");
   Room * r9 = new Room("Kids Room","This room is full of toys. You don't have any interest in them. There is a door to west.");

   Doors * c1southd = new Doors(true);
   Doors * r1southd = new Doors(true);
   Doors * r1eastd = new Doors(true);
   Doors * c10westd = new Doors(true);
   Doors * c3southd = new Doors(true);
   Doors * c5southd = new Doors(true);
   Doors * r6northd = new Doors(true);
   Doors * r6southd = new Doors(true);
   Doors * c7southd = new Doors(true);
   Doors * r8eastd = new Doors(true);
   Doors * r8northd = new Doors(true);
   Doors * c8westd = new Doors(true);
   Doors * c8southd = new Doors(true);
   Doors * c9southd = new Doors(true);
   Doors * r9westd = new Doors(true);
   Doors * c14eastd = new Doors(true);
   Doors * c15eastd = new Doors(false);

   c1->setExtendToSouth(r1);
   c1->setExtendToNorth(NULL);
   c1->setExtendToEast(c2);
   c1->setExtendToWest(NULL);
   c2->setExtendToSouth(NULL);
   c2->setExtendToNorth(NULL);
   c2->setExtendToEast(c3);
   c2->setExtendToWest(c1);
   c3->setExtendToSouth(r4);
   c3->setExtendToNorth(NULL);
   c3->setExtendToEast(c4);
   c3->setExtendToWest(c2);
   c4->setExtendToSouth(NULL);
   c4->setExtendToNorth(NULL);
   c4->setExtendToEast(c5);
   c4->setExtendToWest(c3);
   c5->setExtendToSouth(r6);
   c5->setExtendToNorth(NULL);
   c5->setExtendToEast(c6);
   c5->setExtendToWest(c4);
   c6->setExtendToSouth(NULL);
   c6->setExtendToNorth(NULL);
   c6->setExtendToEast(c7);
   c6->setExtendToWest(c5);
   c7->setExtendToSouth(r8);
   c7->setExtendToNorth(NULL);
   c7->setExtendToEast(NULL);
   c7->setExtendToWest(c6);
   c8->setExtendToSouth(r5);
   c8->setExtendToNorth(NULL);
   c8->setExtendToEast(c9);
   c8->setExtendToWest(r8);
   c9->setExtendToSouth(c15);
   c9->setExtendToNorth(NULL);
   c9->setExtendToEast(r9);
   c9->setExtendToWest(c8);
   c10->setExtendToSouth(NULL);
   c10->setExtendToNorth(NULL);
   c10->setExtendToEast(c11);
   c10->setExtendToWest(r3);
   c11->setExtendToSouth(NULL);
   c11->setExtendToNorth(NULL);
   c11->setExtendToEast(NULL);
   c11->setExtendToWest(c10);
   c12->setExtendToSouth(NULL);
   c12->setExtendToNorth(r6);
   c12->setExtendToEast(c13);
   c12->setExtendToWest(NULL);
   c13->setExtendToSouth(NULL);
   c13->setExtendToNorth(NULL);
   c13->setExtendToEast(c14);
   c13->setExtendToWest(c12);
   c14->setExtendToSouth(NULL);
   c14->setExtendToNorth(NULL);
   c14->setExtendToEast(r5);
   c14->setExtendToWest(c13);
   c15->setExtendToSouth(NULL);
   c15->setExtendToNorth(c9);
   c15->setExtendToEast(r7);
   c15->setExtendToWest(r5);
   r1->setExtendToSouth(r3);
   r1->setExtendToNorth(c1);
   r1->setExtendToEast(r2);
   r1->setExtendToWest(NULL);
   r2->setExtendToSouth(NULL);
   r2->setExtendToNorth(NULL);
   r2->setExtendToEast(NULL);
   r2->setExtendToWest(r1);
   r3->setExtendToSouth(NULL);
   r3->setExtendToNorth(r1);
   r3->setExtendToEast(c10);
   r3->setExtendToWest(NULL);
   r4->setExtendToSouth(NULL);
   r4->setExtendToNorth(c3);
   r4->setExtendToEast(NULL);
   r4->setExtendToWest(NULL);
   r5->setExtendToSouth(NULL);
   r5->setExtendToNorth(c8);
   r5->setExtendToEast(c15);
   r5->setExtendToWest(c14);
   r6->setExtendToSouth(c12);
   r6->setExtendToNorth(c5);
   r6->setExtendToEast(NULL);
   r6->setExtendToWest(NULL);
   r7->setExtendToSouth(NULL);
   r7->setExtendToNorth(NULL);
   r7->setExtendToEast(NULL);
   r7->setExtendToWest(c15);
   r8->setExtendToSouth(NULL);
   r8->setExtendToNorth(c7);
   r8->setExtendToEast(c8);
   r8->setExtendToWest(NULL);
   r9->setExtendToSouth(NULL);
   r9->setExtendToNorth(NULL);
   r9->setExtendToEast(NULL);
   r9->setExtendToWest(c9);

   c1->setDoors(c1southd,NULL,NULL,NULL);
   c2->setDoors(NULL,NULL,NULL,NULL);
   c3->setDoors(c3southd,NULL,NULL,NULL);
   c4->setDoors(NULL,NULL,NULL,NULL);
   c5->setDoors(c5southd,NULL,NULL,NULL);
   c6->setDoors(NULL,NULL,NULL,NULL);
   c7->setDoors(c7southd,NULL,NULL,NULL);
   c8->setDoors(c8southd,NULL,NULL,c8westd);
   c9->setDoors(c9southd,NULL,NULL,NULL);
   c10->setDoors(NULL,NULL,NULL,c10westd);
   c11->setDoors(NULL,NULL,NULL,NULL);
   c12->setDoors(NULL,NULL,NULL,NULL);
   c13->setDoors(NULL,NULL,NULL,NULL);
   c14->setDoors(NULL,NULL,c14eastd,NULL);
   c15->setDoors(NULL,NULL,c15eastd,NULL);
   r1->setDoors(r1southd,NULL,r1eastd,NULL);
   r2->setDoors(NULL,NULL,NULL,NULL);
   r3->setDoors(NULL,NULL,NULL,NULL);
   r4->setDoors(NULL,NULL,NULL,NULL);
   r5->setDoors(NULL,NULL,NULL,NULL);
   r6->setDoors(r6southd,r6northd,NULL,NULL);
   r7->setDoors(NULL,NULL,NULL,NULL);
   r8->setDoors(NULL,r8northd,r8eastd,NULL);
   r9->setDoors(NULL,NULL,NULL,r9westd);

//initializing items...
Item * sword = new Item("Sword","A sharp sword which has excellent craftsmanship.",4000.00);
Item * shield = new Item("Shield","A shield with a beautiful banner on it.", 3000.00);
Item * letter10 = new Item("Letter","This is a letter written in a beautiful handwriting.", 10.00);
Item * letter11 = new Item("Letter","There is a hastily written text on the paper.", 11.00);
Item * rustyKey = new Item("Rusty Key", "This is an old rusty key. Its handle is heart shaped.", 100.00);
Item * ironKey = new Item("Iron Key", "This is an iron key. It is old and has a diamond shaped handle.",200.00);
Item * broom = new Item("Broom","This is a broom for cleaning. It is almost brand new, like it has never been used.",1000.00);
Item * coins = new Item("Coins","Worth billions of dollars.",2000000.00);
   c1->setRoomInventory(sword);
   c1->setRoomInventory(shield);
   // this causes program to crash :c2->setRoomInventory(NULL);

   c5->setRoomInventory(letter10);
   c13->setRoomInventory(letter11);
   r2->setRoomInventory(rustyKey);
   r2->setRoomInventory(ironKey);
   r2->setRoomInventory(broom);
   r7->setRoomInventory(coins);

string action;
openSouthCommand * southdoorc = new openSouthCommand();
openNorthCommand * northdoorc = new openNorthCommand();
openEastCommand * eastdoorc = new openEastCommand();
openWestCommand * westdoorc = new openWestCommand();
Item * leadItem =new Item("empty","space",0.00);
UseCommands * oneCommand = new UseCommands();

   Character * gameChar = Character::createInstance("Beril Bayer", "I am one little enthusiastic player for this game.", c1);
   Room * currentRoom;
   southdoorc->setCharacterForCommand(gameChar);
    northdoorc->setCharacterForCommand(gameChar);
   eastdoorc->setCharacterForCommand(gameChar);
   westdoorc->setCharacterForCommand(gameChar);
   oneCommand->setCommander(gameChar);
   currentRoom = gameChar->getCurrentRoom();
   gameChar->info();
   //gameChar->takeItem(shield);

   while(1){
    cout<<endl;
   getline(cin,action);

   if(action == "take sword"){
    gameChar->takeItem(sword);
   }
   else if(action == "take shield"){
    gameChar->takeItem(shield);
   }
   else if((action=="take letter") &&gameChar->getCurrentRoom()==c5){
    gameChar->takeItem(letter10);
   }
   else if((action=="take letter")&& gameChar->getCurrentRoom()== c13){
    gameChar->takeItem(letter11);
   }
   else if(action=="take rusty key"){
    gameChar->takeItem(rustyKey);
   }
   else if(action=="take iron key"){
    gameChar->takeItem(ironKey);
   }
   else if(action=="take broom"){
    gameChar->takeItem(broom);
   }
   else if(action=="take coins"){
    gameChar->takeItem(coins);
   }
   else if((action=="move south")&& currentRoom->getDoorToSouth() !=NULL){
        cout<<"There is a door to south, but it is closed.Write -open south- to open it."<<endl;
   }
   else if(action=="move south"){
    gameChar->moveDirection("SOUTH");
    gameChar->info();
   }

   else if((action=="move north") && currentRoom->getDoorToNorth() !=NULL){
        cout<<"There is a door to north, but it is closed.Write -open north- to open it."<<endl;
   }
   else if(action=="move north" ){
    gameChar->moveDirection("NORTH");
    gameChar->info();
   }

   else if((action=="move east") && currentRoom->getDoorToEast() !=NULL && currentRoom->getDoorToEastState()==false){
    cout<<"The door is locked. You need the key to open it."<<endl;
   }
   else if((action=="move east") && currentRoom->getDoorToEast() !=NULL){
        cout<<"There is a door to east, but it is closed.Write -open east- to open it."<<endl;
   }
   else if(action=="move east"){
    gameChar->moveDirection("EAST");
    gameChar->info();
   }

   else if((action=="move west") && currentRoom->getDoorToWest() !=NULL){
        cout<<"There is a door to west, but it is closed.Write -open west- to open it."<<endl;
   }
   else if(action=="move west"){
    gameChar->moveDirection("WEST");
    gameChar->info();
   }
   else if(action=="open south" ){
    southdoorc->openSouth();
   gameChar->info();
   }
   else if(action=="open north" ){
    northdoorc->openNorth();
    gameChar->info();
   }
   else if(action=="open east") {
    eastdoorc->openEast();
    gameChar->info();
   }
   else if(action=="open west"){
    westdoorc->openWest();
    gameChar->info();
   }
   else if((action=="use letter")&& gameChar->getCurrentRoom() ==c5){
    oneCommand->readLetter10();
   }
   else if((action=="use letter") && gameChar->getCurrentRoom() ==c13){
    oneCommand->readLetter11();
   }
   else if(action=="use broom"){
    oneCommand->broomUse();
   }
   else if(action=="use iron key"){

        oneCommand->setCurrentRoom(gameChar->getCurrentRoom());
    oneCommand->IronKeyUse();
   gameChar->info();
   }
   else if(action =="exit"){
    break;
   }

   }

return 0 ;
}
