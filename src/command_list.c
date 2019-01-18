#include "player.h"
#include "unit.h"
#include "unitList.h"
#include "building.h"
#include "buildingList.h"
#include "printformat.h"
#include "map.h"
#include "./Point/point.h"
#include "moveStack.h"


int countMove (Point P1, Point P2)
// menghitung banyaknya move yang dilakukan untuk berpindah dari P1 ke P2
{
	int moveX, moveY;

	moveX= (P1).X - (P2).X;

	if (moveX<0)
		moveX*=-1;

	moveY= (P1).Y - (P2).Y;
	if (moveY<0)
		moveY*=-1;

	return (moveX + moveY);
}

void Move(Queue *Q, Player *P, Map *M)
// Tampilkan kemungkinan jalan yang mungkin
// Unit bergerak ke lokasi yang bertanda #
// apabila merupakan village, village jadi milik player tersebut
{
	Point Po, Pos;
	boolean canMove, noEnemy;
	char *buf;
	int i,j;

	if (UnitInfo((P)->currentUnit).movementPoint==0) {
		printf("\nThe unit doesn't have any move point for this turn.\n");
		canMove=false;
	}
	else {
		//MENAMPILKAN PATH YANG MUNGKIN DIAMBIL DENGAN # (TYPE = 5)
		//ke kanan
		noEnemy=true;
		i=UnitInfo((P)->currentUnit).location.X+1;
		while ((i<= UnitInfo((P)->currentUnit).location.X + getMovementPoint(UnitInfo((P)->currentUnit))) && noEnemy) {
			j= UnitInfo((P)->currentUnit).location.Y;
			if ((M)->MapTable[j][i].unit.type==0) {
				//Jika petak sebelumnya kosong, atau tidak kosong tapi bukan musuh
				if (((M)->MapTable[j][i-1].unit.type==0) || ((M)->MapTable[j][i-1].unit.type==5) || ((M)->MapTable[j][i-1].unit.playerID==getID(*P)))
					(M)->MapTable[j][i].unit.type=5;
				else
					noEnemy=false;
			}
			i++;
		}

		//ke kiri
		noEnemy=true;
		i=UnitInfo((P)->currentUnit).location.X-1;
		while ((i>= UnitInfo((P)->currentUnit).location.X - getMovementPoint(UnitInfo((P)->currentUnit))) && noEnemy) {
			j= UnitInfo((P)->currentUnit).location.Y;
			if ((M)->MapTable[j][i].unit.type==0) {
				//Jika petak sebelumnya kosong, atau tidak kosong tapi bukan musuh
				if (((M)->MapTable[j][i+1].unit.type==0) || ((M)->MapTable[j][i+1].unit.type==5) || ((M)->MapTable[j][i+1].unit.playerID==getID(*P)))
					(M)->MapTable[j][i].unit.type=5;
				else
					noEnemy=false;
			}
			i--;
		}

		//ke bawah
		noEnemy=true;
		j= UnitInfo((P)->currentUnit).location.Y+1;
		while ((j<= UnitInfo((P)->currentUnit).location.Y + getMovementPoint(UnitInfo((P)->currentUnit))) && noEnemy) {

			i=UnitInfo((P)->currentUnit).location.X;
			if ((M)->MapTable[j][i].unit.type==0) {
				//Jika petak sebelumnya kosong, atau tidak kosong tapi bukan musuh
				if (((M)->MapTable[j-1][i].unit.type==0) || ((M)->MapTable[j-1][i].unit.type==5) || ((M)->MapTable[j-1][i].unit.playerID==getID(*P)))
					(M)->MapTable[j][i].unit.type=5;
				else
					noEnemy=false;
			}
			j++;
		}

		//ke atas
		noEnemy=true;
		j= UnitInfo((P)->currentUnit).location.Y-1;
		while ((j>= UnitInfo((P)->currentUnit).location.Y - getMovementPoint(UnitInfo((P)->currentUnit))) && noEnemy) {
			i=UnitInfo((P)->currentUnit).location.X;
			if ((M)->MapTable[j][i].unit.type==0) {
				//Jika petak sebelumnya kosong, atau tidak kosong tapi bukan musuh
				if (((M)->MapTable[j+1][i].unit.type==0) || ((M)->MapTable[j+1][i].unit.type==5) || ((M)->MapTable[j+1][i].unit.playerID==getID(*P)))
					(M)->MapTable[j][i].unit.type=5;
				else
					noEnemy=false;
			}
			j--;
		}
		printMap(*M,*Q);


		do {
			printf("\n\nPlease ​ ​enter ​ ​cell’s ​ ​coordinate ​ ​x ​ ​y: ​ ​​");
			BacaPoint(&Pos);
			if ((M)->MapTable[(Pos).Y][(Pos).X].unit.type==5)
				canMove=true;
			else
				canMove=false;
			clearScreen();
			if (!canMove) {
				printMap(*M,*Q);
				printf("\nYou ​ ​can’t ​ ​move ​ ​there\n");
			}

		} while (!canMove);
	}

	if (canMove) {
		//Simpan move di movement stack
		PushMove(&(UnitInfo((P)->currentUnit).stackMovement), Pos);
		//Kurangi movementpoint
		UnitInfo((P)->currentUnit).movementPoint -= countMove(Pos, getUnitLocation(UnitInfo((P)->currentUnit))) ;
		//Move unit ke location
		UnitInfo((P)->currentUnit).location.X = (Pos).X;
		UnitInfo((P)->currentUnit).location.Y = (Pos).Y;

		//Jika move ke village kosong, village itu jadi milik dia

		Building Bu= (M)->MapTable[(Pos).Y][(Pos).X].building;
		if ((Bu.type==VILLAGE && Bu.playerID==KOSONG)) {
			RemoveBuilding(&(M)->villageList, getBuildingAddressByLocation((M)->villageList,Pos));
			Bu.playerID = getID(*P);
			AddBuilding(&(P)->buildingList, Bu);
			updateMap(M,*Q);
			//Set movement point = 0 & empty stack
			UnitInfo((P)->currentUnit).movementPoint=0;
			CreateStack(&UnitInfo((P)->currentUnit).stackMovement);
		}

		//Jika move ke village milik dia, health jadi full
		if ((Bu.type==VILLAGE) && (Bu.playerID==getID(*P))) {
			if (UnitInfo((P)->currentUnit).type==KING_TYPE)
				UnitInfo((P)->currentUnit).health==KING_MAX_HEALTH;
			else if (UnitInfo((P)->currentUnit).type==ARCHER_TYPE)
				UnitInfo((P)->currentUnit).health==ARCHER_MAX_HEALTH;
			else if (UnitInfo((P)->currentUnit).type==SWORDSMAN_TYPE)
				UnitInfo((P)->currentUnit).health==SWORDSMAN_MAX_HEALTH;
			else  if (UnitInfo((P)->currentUnit).type==MAGE_TYPE)
				UnitInfo((P)->currentUnit).health==MAGE_MAX_HEALTH;
		}

		printf("You ​ ​have ​ ​successfully ​ ​moved ​ ​to ​ ​(%d, %d)\n", (Pos).X, (Pos).Y);

		//BALIKIN KE KOSONG PATHNYA
		i=UnitInfo((P)->currentUnit).location.X+1;
		while ((i<= UnitInfo((P)->currentUnit).location.X + getMovementPoint(UnitInfo((P)->currentUnit)))) {
			j= UnitInfo((P)->currentUnit).location.Y;
			if ((M)->MapTable[j][i].unit.type==0) {
				//Jika petak sebelumnya kosong, atau tidak kosong tapi bukan musuh
				if ((M)->MapTable[j][i-1].unit.type==5)
					(M)->MapTable[j][i].unit.type=0;
			}
			i++;
		}

		//ke kiri
		i=UnitInfo((P)->currentUnit).location.X-1;
		while ((i>= UnitInfo((P)->currentUnit).location.X - getMovementPoint(UnitInfo((P)->currentUnit)))) {
			j= UnitInfo((P)->currentUnit).location.Y;
			if ((M)->MapTable[j][i].unit.type==0) {
				//Jika petak sebelumnya kosong, atau tidak kosong tapi bukan musuh
				if ((M)->MapTable[j][i+1].unit.type==5)
					(M)->MapTable[j][i].unit.type=0;
			}
			i--;
		}

		//ke bawah
		j= UnitInfo((P)->currentUnit).location.Y+1;
		while ((j<= UnitInfo((P)->currentUnit).location.Y + getMovementPoint(UnitInfo((P)->currentUnit)))) {
			i=UnitInfo((P)->currentUnit).location.X;
			if ((M)->MapTable[j][i].unit.type==0) {
				//Jika petak sebelumnya kosong, atau tidak kosong tapi bukan musuh
				if ((M)->MapTable[j+1][i].unit.type==5)
					(M)->MapTable[j][i].unit.type=0;
			}
			j++;
		}

		//ke atas
		j= UnitInfo((P)->currentUnit).location.Y-1;
		while ((j>= UnitInfo((P)->currentUnit).location.Y - getMovementPoint(UnitInfo((P)->currentUnit)))) {
			i=UnitInfo((P)->currentUnit).location.X;
			if ((M)->MapTable[j][i].unit.type==0) {
				//Jika petak sebelumnya kosong, atau tidak kosong tapi bukan musuh
				if ((M)->MapTable[j-1][i].unit.type==5)
					(M)->MapTable[j][i].unit.type=0;
			}
			j--;
		}
	}

}

void ChangeUnit(Player *P)
/*Mengganti current unit menjadi unit lain yang sudah dimiliki player*/
{
	address A, units[100];
	int i, number, totalUnits;

	//Hapus movement stack unit sebelumnya
	CreateStack(&UnitInfo((P)->currentUnit).stackMovement);
	Point Pos = (UnitInfo((P)->currentUnit).location);
	PushMove(&UnitInfo((P)->currentUnit).stackMovement,Pos);
	printf("\n" );printUnitInfo((P)->unitList);
	A= FirstUL((P)->unitList);
	i=1;

	if (!IsEmptyUL((P)->unitList)){
		units[i]= A;
		A = NextUL(A);
		i++;
		while (A != FirstUL((P)->unitList)) {
			units[i]= A;
			A= NextUL(A);
			i++;
		}
	}
	totalUnits=i;

	do {
		printf("\nPlease ​ ​enter ​ ​the ​ ​no. ​ ​of ​ ​unit ​ ​you ​ ​want ​ ​to ​ ​select: ");
		scanf("%d", &number);
	} while (number>totalUnits);

	if (UnitInfo(units[number]).type==KING_TYPE) {
		printf("You ​ ​are ​ ​now ​ ​selecting ​King\n");
	} else if (UnitInfo(units[number]).type==ARCHER_TYPE) {
		printf("You ​ ​are ​ ​now ​ ​selecting ​Archer\n");
	} else if (UnitInfo(units[number]).type==SWORDSMAN_TYPE) {
		printf("You ​ ​are ​ ​now ​ ​selecting ​Swordsman\n");
	} else if (UnitInfo(units[number]).type==MAGE_TYPE) {
		printf("You ​ ​are ​ ​now ​ ​selecting ​White Mage\n");
	}

	(P)->currentUnit=units[number];
}

void Recruit(Player *P, Map M)
/*Merekrut suatu unit baru di Castle yang dimiliki player,
	dan dilakukan oleh King yang berada di Tower */
{
	Point Po;
	int type;
	Building B;
	UnitList UL;
	address UAdr;
	boolean canRecruit;
	Point T;

	(T).X =UnitInfo((P)->currentUnit).location.X;
	(T).Y =UnitInfo((P)->currentUnit).location.Y;
	if (UnitInfo((P)->currentUnit).type == KING_TYPE) {
		if ((M).MapTable[(T).Y][(T).X].building.type== TOWER) {
				if ((P)->gold>=20) {
						//HAPUS MOVEMENT STACK
					CreateStack(&UnitInfo((P)->currentUnit).stackMovement);
					Point Pos = (UnitInfo((P)->currentUnit).location);
					PushMove(&UnitInfo((P)->currentUnit).stackMovement,Pos);
					//PEMASUKAN KOORDINAT REKRUT
					do 	{
							printf("\nEnter coordinate of empty castle: ");
							BacaPoint(&Po);
							(B).type=(M).MapTable[(Po).Y][(Po).X].building.type;
						(B).location=(M).MapTable[(Po).Y][(Po).X].building.location;
						(B).playerID=(M).MapTable[(Po).Y][(Po).X].building.playerID;
						//JIKA B BUKAN CASTLE ATAU BUKAN CASTLE DIA
						if ((B).type!=CASTLE) {
							printf("You're not in your castle.\n");
							canRecruit=false;
						} else {
							 if ((B).playerID==UnitInfo((P)->currentUnit).playerID) {
								if ((M).MapTable[(Po).Y][(Po).X].unit.type!=KOSONG) {
									printf("That castle is occupied!\n");
									canRecruit=false;
								} else {
									canRecruit=true;
								}
							 } else {
								printf("You're not in your castle.\n");
								canRecruit=false;
							 }
						}
					} while (!canRecruit);

					if (canRecruit) {
						boolean recruited=false;
						printf("=== ​ ​List ​ ​of ​ ​Recruits ​ ​===\n");
							printf("%d. Archer | Health %d | Attack Type Ranged | Attack Point %d | Price %d\n" , ARCHER_TYPE-1, ARCHER_MAX_HEALTH, ARCHER_ATTACK_POINTS, ARCHER_PRICE);
							printf("%d. Swordsman| Health %d | Attack Type Melee | Attack Point %d | Price %d\n" , SWORDSMAN_TYPE-1, SWORDSMAN_MAX_HEALTH, SWORDSMAN_ATTACK_POINTS, SWORDSMAN_PRICE);
							printf("%d. White Mage | Health %d | Attack Type Melee | Attack Point %d | Price %d\n" , MAGE_TYPE-1, MAGE_MAX_HEALTH, MAGE_ATTACK_POINTS, MAGE_PRICE);
							printf("Enter ​ ​no. ​ ​of ​ ​unit ​ ​you ​ ​want ​ ​to ​ ​recruit: ​ ​");
							scanf("%d", &type);
							clearScreen();
							printf("\n" );
							type++;
							if (type==ARCHER_TYPE) {
								if ((P)->gold>=ARCHER_PRICE) {
									UL=getUnitList(*P);
									AddArcher(&UL);
									decreaseGold(P, ARCHER_PRICE);
									recruited=true;
									printf("You ​have ​recruited ​ ​an ​ ​Archer!\n");
								} else
									printf("Sorry, you don't have enough gold.\n");
							} else if (type==SWORDSMAN_TYPE) {
								if ((P)->gold>=SWORDSMAN_PRICE) {
									UL=getUnitList(*P);
									AddSwordsman(&UL);
									decreaseGold(P, SWORDSMAN_PRICE);
									recruited=true;
									printf("You ​have ​recruited ​a Swordsman!\n");
								} else
									printf("Sorry, you don't have enough gold.\n");
							} else if (type==MAGE_TYPE) {
								if ((P)->gold>=MAGE_PRICE) {
									UL=getUnitList(*P);
									AddMage(&UL);
									decreaseGold(P, MAGE_PRICE);
									recruited=true;
									printf("You ​have ​recruited ​a White Mage!\n");
								} else
									printf("Sorry, you don't have enough gold!\n");
							}
							printf("\n" );
							//Set location unit baru di Castle
							if (recruited) {
								UAdr=FirstUL(UL);
								do {
									UAdr=NextUL(UAdr);
								} while (NextUL(UAdr)!=FirstUL(UL));
								UnitInfo(UAdr).location.X= (Po).X;
								UnitInfo(UAdr).location.Y= (Po).Y;
								UnitInfo(UAdr).playerID= (P)->ID;
								UnitInfo(UAdr).movementPoint= 0;
								PushMove(&UnitInfo(UAdr).stackMovement,Po);
							}
					}
				} else {
					printf("You don't have enough gold to recruit any unit.\n");
				}
		} else {
			printf("You're not in your Tower!\n");
		}
	} else {
		printf("Only a King can recruit a unit.\n");
	}
}

void Undo(Player *P)
/*Mengembalikan suatu unit ke lokasi sebelumnya, selama player tidak melakukan
	fitur recruit, change_unit, attack, atau move ke village */
{
	Point Ptemp;

	PopMove(&(UnitInfo((P)->currentUnit).stackMovement), &Ptemp);

	if (!IsEmptyStack((UnitInfo((P)->currentUnit).stackMovement)) ) {
		if ((UnitInfo((P)->currentUnit).location.X==(Ptemp).X) && (UnitInfo((P)->currentUnit).location.Y==(Ptemp).Y)) {
			PopMove(&UnitInfo((P)->currentUnit).stackMovement, &Ptemp);
		}
		//KEMBALIKAN MOVE POINT
		UnitInfo((P)->currentUnit).movementPoint += countMove(Ptemp, UnitInfo((P)->currentUnit).location);

		//KEMBALIKAN MOVE LOCATION
		UnitInfo((P)->currentUnit).location.X= (Ptemp).X;
		UnitInfo((P)->currentUnit).location.Y= (Ptemp).Y;
		printf("You've successfully moved to (%d,%d)", (Ptemp).X, (Ptemp).Y);
	} else {
		printf("No moves. \n");
	}
	PushMove(&(UnitInfo((P)->currentUnit).stackMovement),(Ptemp));
}


void NextUnit(Player *P){
	address cU = (P)->currentUnit;
	address unitNow = cU;
	cU = NextUL(cU);

	while (cU !=unitNow && ((UnitInfo(cU).movementPoint==0) && (UnitInfo(cU).hasAttacked==true))) {
		cU=NextUL(cU);
	}

	(P)->currentUnit = cU;
}


void switchNumType(int N){
	if (N==KING_TYPE){
		printf("King");
	}
	else 	if (N==ARCHER_TYPE){
		printf("Archer");
	}
	else 	if (N==SWORDSMAN_TYPE){
		printf("Swordsman");
	}
	else 	if (N==MAGE_TYPE){
		printf("Mage");
	}
}

address searchUnit(UnitList L, Unit U){
 // return the address where a specific unit is placed in a list
	boolean found = false;
	address Penemy = FirstUL(L);
	if (Penemy!=Nil){
	 int locY = U.location.Y;
	 int locX = U.location.X;
	 if ((UnitInfo(Penemy).location.X==locX)&&(UnitInfo(Penemy).location.Y==locY))
		 found = true;
	 else Penemy = NextUL(Penemy);

	 while ((Penemy!=FirstUL(L))&&(found==false)){
		 if ((UnitInfo(Penemy).location.X==locX)&&(UnitInfo(Penemy).location.Y==locY))
			 found = true;
		 else
			 Penemy = NextUL(Penemy);
	 }
	}
	if (found){

		return Penemy;
	}
	else {
		return Nil;
	}
}

boolean isDead(Unit U){
//Check Unit's health if its dead or alive
	return (U.health <= 0);
}

void Attack (Map M, Player *P1, Player *P2)
//Command ​ini akan menampilkan unit-unit musuh apa saja yang dapat diserang.
//Unit-unit musuh yang dapat diserang adalah unit-unit yang ​adjacent ​di petak
//atas, ​ ​kanan, ​ ​kiri, ​ ​atau ​ ​bawah ​ ​dari ​ ​unit ​ ​saat ​ ​ini.
// Suatu unit hanya dapat menyerang sebanyak 1x setiap turn, yaitu ketika properti
//kesempatan ​ ​serangan ​ ​TRUE.
// Setelah melakukan ​command ​ATTACK, nilai ​movement point unit penyerang
//nilainya ​ ​diubah ​ ​menjadi ​ ​0, ​ ​dan ​ ​properti ​ ​kesempatan ​ ​serangan ​ ​menjadi ​ ​FALSE.
// kamus
//manfaatin current unit
// minta input point mana yang bisa diserang
{
	Unit yourUnit = UnitInfo((P1)->currentUnit);
	Point Pn,Ps,Pe,Pw;
	Point P = 	UnitInfo((P1)->currentUnit).location; // get current location of the unit
	int optN = -1;
	int optS = -1;
	int optE = -1;
	int optW = -1;

	// SET ADJACENT LOCATION
	Pn.Y = P.Y - 1;	// NORTH
	Pn.X = P.X;
	Ps.Y = P.Y + 1; // SOUTH
	Ps.X = P.X;
	Pe.Y = P.Y; // EAST
	Pe.X = P.X + 1;
	Pw.Y = P.Y; // WEST
	Pw.X = P.X - 1;

	int i = 0;
	Unit X;
	// CHECK UNITS IN ADJACENT LOCATIONS
	if (getUnit(M,Pn).type!=0 && getUnit(M,Pn).playerID!=yourUnit.playerID ){
		i++;
		optN = i;
		X = getUnit(M,Pn);
		printf("%d. ",i);
		switchNumType(X.type);
		printf(" (%d,%d) | Health %d/%d ",Pn.X,Pn.Y,X.health,X.maxHealth);
		if (X.attackType==yourUnit.attackType || X.type == KING_TYPE)
			printf("(Retaliates)\n");
	}
	if (getUnit(M,Ps).type!=0 && getUnit(M,Ps).playerID!=yourUnit.playerID){
		i++;
		optS = i;
		X = getUnit(M,Ps);
		printf("%d. ",i);
		switchNumType(X.type);
		printf(" (%d,%d) | Health %d/%d ",Ps.X,Ps.Y,X.health,X.maxHealth);
		if (X.attackType==yourUnit.attackType || X.type == KING_TYPE)
			printf("(Retaliates)\n");
		printf("\n");
	}
	if (getUnit(M,Pe).type!=0 && getUnit(M,Pe).playerID!=yourUnit.playerID){
		i++;
		optE = i;
		X = getUnit(M,Pe);
		printf("%d. ",i);
		switchNumType(X.type);
		printf(" (%d,%d) | Health %d/%d ",Pe.X,Pe.Y,X.health,X.maxHealth);
		if (X.attackType==yourUnit.attackType || X.type == KING_TYPE)
			printf("(Retaliates)\n");
		printf("\n");
	}
	if (getUnit(M,Pw).type!=0 && getUnit(M,Pw).playerID!=yourUnit.playerID){
		i++;
		optW = i;
		X = getUnit(M,Pw);
		printf("%d. ",i);
		switchNumType(X.type);
		printf(" (%d,%d) | Health %d/%d ",Pw.X,Pw.Y,X.health,X.maxHealth);
		if (X.attackType==yourUnit.attackType || X.type == KING_TYPE)
			printf("(Retaliates)\n");
		printf("\n");
	}

	// SELECTING ENEMY TO BE ATTACKED
	if (i!=0){
		printf("Select the enemy you want to attack: ");
		int enemy;
		boolean chosen = false;
		Unit enemyUnit;
		scanf("%d",&enemy);
		if (enemy == optN){
			enemyUnit = getUnit(M,Pn);
			chosen = true;
		}
		else if (enemy == optS){
			enemyUnit = getUnit(M,Ps);
			chosen = true;
		}
		else if (enemy == optE){
			enemyUnit = getUnit(M,Pe);
			chosen = true;
		}
		else if (enemy == optW){
			enemyUnit = getUnit(M,Pw);
			chosen = true;
		}

		if (chosen){
				// clearScreen();
			// SEARCH ADDRESSES IN UNIT LIST (TO MODIFY THERE)
			address Penemy = searchUnit((P2)->unitList, enemyUnit);
			address PyourUnit = searchUnit((P1)->unitList,UnitInfo((P1)->currentUnit));

			if (Penemy!=Nil){

			int amount = yourUnit.attackPoint;
			decreaseHealth(&UnitInfo(Penemy),amount);
			printf("Enemy's ");
			switchNumType(UnitInfo(Penemy).type);
			printf(" is damaged by %d.\n",amount);
			setHasAttacked(&(UnitInfo((P1)->currentUnit)),true);


			// ENEMY RETALIATES IF THEY HAVE THE SAME TYPE
			if (UnitInfo(Penemy).attackType == yourUnit.attackType || UnitInfo(Penemy).type == KING_TYPE ){
				if (UnitInfo(Penemy).health > 0){
					printf("Enemy's ");
					switchNumType(UnitInfo(Penemy).type);
					printf(" retaliates.");
					decreaseHealth(&(UnitInfo(PyourUnit)),amount);
					printf(" Your ");
					switchNumType(UnitInfo(PyourUnit).type);
					printf(" is damaged by %d.\n",amount);
				}
			}

			// CHECKING IF OUR UNIT IS STILL ALIVE
			if (isDead(UnitInfo(PyourUnit))){
				printf("Your ");
				switchNumType(UnitInfo(PyourUnit).type);
				printf(" is Dead :(\n");
				DeleteUnit(&((P1)->unitList),PyourUnit);
				updateCurrentUnit(P1);
			}
			if (isDead(UnitInfo(Penemy))) {
				printf("The ");
				switchNumType(UnitInfo(Penemy).type);
				printf("'s Enemy is dead! Great job!\n");
				DeleteUnit(&((P2)->unitList),Penemy);

			}
			}

			(UnitInfo(PyourUnit)).hasAttacked  = true;
			setMovementPoint(&UnitInfo(PyourUnit),0);
		}
		else printf("Wrong choice input.\n");
	}
	else{
		printf("\nNo enemy nearby.\n" );
	}
}


void PrintBbyID (Building B, Player P1, Player P2)
{
	if (B.type != 0){
		printf("== Cell Info ==\n");
		if (B.type == 1){
			printf("Village\n");
		}
		else if (B.type == 2){
			printf("Castle\n");
		}
		else if (B.type == 3){
			printf("Tower\n");
		}
		if (B.playerID != 0){
			if (B.playerID == getID(P1)){
				printf("Owned by Player 1\n");
			}
			else if (B.playerID == getID(P2)){
				printf("Owned by Player 2\n");
			}
		}
	}
}

address searchUnitType(UnitList L, int X){
 // return the address where a specific unit is placed in a list
	boolean found = false;
	address Penemy = FirstUL(L);
	if (Penemy!=Nil){
	 if (UnitInfo(Penemy).type==X)
		 found = true;
	 else Penemy = NextUL(Penemy);

	 while ((Penemy!=FirstUL(L))&&(found==false)){
		 if (UnitInfo(Penemy).type==X)
			 found = true;
		 else
			 Penemy = NextUL(Penemy);
	 }
	}
	if (found)
		return Penemy;
	else
		return Nil;
}

void incHealthWhiteMage(Unit *U, int amount){
// Increase the health of an unit and full-health-handling

	if ((U)->type == KING_TYPE && (U)->health < KING_MAX_HEALTH){
		increaseHealth(U,amount);
		if ((U)->health > KING_MAX_HEALTH)
			(U)->health = KING_MAX_HEALTH;
	}
	else if ((U)->type == ARCHER_TYPE && (U)->health < ARCHER_MAX_HEALTH){
		increaseHealth(U,amount);
		if ((U)->health > ARCHER_MAX_HEALTH)
			(U)->health = ARCHER_MAX_HEALTH;
	}
	else if ((U)->type == MAGE_TYPE && (U)->health < MAGE_MAX_HEALTH){
		increaseHealth(U,amount);
		if ((U)->health > MAGE_MAX_HEALTH)
			(U)->health = MAGE_MAX_HEALTH;
	}
	else if ((U)->type == SWORDSMAN_TYPE && (U)->health < SWORDSMAN_MAX_HEALTH){
		increaseHealth(U,amount);
		if ((U)->health > SWORDSMAN_MAX_HEALTH)
			(U)->health = SWORDSMAN_MAX_HEALTH;
	}
}

void whiteMageHealProcess(Map M, Player *Pl, address Pwhite){
// Heals the player's Unit that is adjacent to the player's white mage location
	Point Pn,Ps,Pe,Pw;
	if (Pwhite != Nil){
		Unit yourUnit = UnitInfo(Pwhite);
		Point P = UnitInfo(Pwhite).location; // get current location of the unit
		// SET ADJACENT LOCATION
		Pn.Y = P.Y - 1;	// NORTH
		Pn.X = P.X;
		Ps.Y = P.Y + 1; // SOUTH
		Ps.X = P.X;
		Pe.Y = P.Y; // EAST
		Pe.X = P.X + 1;
		Pw.Y = P.Y; // WEST
		Pw.X = P.X - 1;

		Unit X;
		address Pcurrent;
		// CHECK UNITS IN ADJACENT LOCATIONS
		if (getUnit(M,Pn).type!=0 && getUnit(M,Pn).playerID==yourUnit.playerID ){
			X = getUnit(M,Pn);
			Pcurrent = searchUnit((Pl)->unitList,X);
			if (Pcurrent!=Nil){
				incHealthWhiteMage(&UnitInfo(Pcurrent), 5);
			}
		}
		if (getUnit(M,Ps).type!=0 && getUnit(M,Ps).playerID==yourUnit.playerID){
			X = getUnit(M,Ps);
			Pcurrent = searchUnit((Pl)->unitList,X);
			if (Pcurrent!=Nil){
				incHealthWhiteMage(&UnitInfo(Pcurrent), 5);
			}
		}
		if (getUnit(M,Pe).type!=0 && getUnit(M,Pe).playerID==yourUnit.playerID){
			X = getUnit(M,Pe);
			Pcurrent = searchUnit((Pl)->unitList,X);
			if (Pcurrent!=Nil){
				incHealthWhiteMage(&UnitInfo(Pcurrent), 5);
			}
		}
		if (getUnit(M,Pw).type!=0 && getUnit(M,Pw).playerID==yourUnit.playerID){
			X = getUnit(M,Pw);
			Pcurrent = searchUnit((Pl)->unitList,X);
			if (Pcurrent!=Nil){
				incHealthWhiteMage(&UnitInfo(Pcurrent), 5);
			}
		}
  }
}

void whiteMageHealing(Map M, Player *P){
 // search white Mage in UnitList and heals other units in adjacent location
	address Pwhite = FirstUL((P)->unitList);
	if (Pwhite!=Nil){
	 if (UnitInfo(Pwhite).type==MAGE_TYPE){
		 whiteMageHealProcess(M, P, Pwhite);
	 }
	 Pwhite = NextUL(Pwhite);

	 while (Pwhite!=FirstUL((P)->unitList)){
		 if (UnitInfo(Pwhite).type==MAGE_TYPE){
			 whiteMageHealProcess(M, P, Pwhite);
		 }
		 Pwhite = NextUL(Pwhite);
	 }
	}
}

void PrintUbyID (Unit U, Player P1, Player P2)
{
	if ((U).type != 0){
		printf("== Unit Info ==\n");
		if (U.type == 1){
			printf("King\n");
		}
		else if (U.type == 2){
			printf("Archer\n");
		}
		else if (U.type == 3){
			printf("Swordsman\n");
		}
		else if (U.type == 4){
			printf("Mage\n");
		}
		if ((U).playerID != 0){
			if (U.playerID == PLAYER1){
				printf("Owned by Player 1\n");
			}
			else if ((U).playerID == PLAYER2){
				printf("Owned by Player 2\n");
			}
		}
		printf("Health ");
		printf("%d",U.health);
		printf("/");
		printf("%d",U.maxHealth);
		printf(" | ATK ");
		printf("%d\n",U.attackPoint);
	}
}


void InfoCell(Map M, Player P1, Player P2)
// Command ​ini akan memberikan informasi mengenai suatu petak, baik jenis dari petak
//tersebut (contoh: petak biasa, petak Tower pemain merah, dll.) maupun unit yang
//sedang ​ ​berada ​ ​di ​ ​petak​ ​tersebut ​ ​(contoh: ​ ​unit ​ ​Archer, ​ ​health ​ ​50, ​ ​dll.)
//kamus
{
	Unit U;
	Building B;
	int x, y;


	printf("\nEnter the coordinate of the cell: ");

	scanf("%d %d",&x,&y);
	(B).type=(M).MapTable[y][x].building.type;
	(B).location=(M).MapTable[y][x].building.location;
	(B).playerID=(M).MapTable[y][x].building.playerID;
	printf("\n");
	PrintBbyID(B, P1, P2);
	printf("\n");
	(U).type=(M).MapTable[y][x].unit.type;
	(U).location=(M).MapTable[y][x].unit.location;
	(U).playerID=(M).MapTable[y][x].unit.playerID;
	(U).health=(M).MapTable[y][x].unit.health;
	(U).maxHealth = (M).MapTable[y][x].unit.maxHealth;
	(U).attackPoint=(M).MapTable[y][x].unit.attackPoint;
	PrintUbyID(U,P1,P2);
}
