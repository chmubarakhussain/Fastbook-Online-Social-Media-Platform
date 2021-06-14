#include<iostream>
#include<fstream>
//#include<vld.h>
#pragma warning(disable : 4996)
using namespace std;

//class declarations
class Helper;
class Object;
class Date;
class FastBook;
class User;
class Page;
class Post;
class Comment;

//class definitions
class Helper
{
public:
	static int calculateNumberOfDigits(int num)
	{
		int i = 0;
		while (num != 0)
		{
			num = num / 10;
			i++;
		}
		return i;
	}
	static void strCopy(char* s1, const char* str2)
	{
		int i = 0;
		while (str2[i] != '\0')
		{
			s1[i] = str2[i];
			i++;
		}
		s1[i] = '\0';
	}
	static bool strFind(const char* whereFind, const char* toFind)
	{
		int i = 0;
		bool flag = true;
		while (whereFind[i] != '\0')
		{
			if (whereFind[i] == toFind[0])
			{
				//entered in loop to search word
				for (int j = 0; toFind[j] != '\0'; j++)
				{
					if (whereFind[i] != toFind[j])
					{
						flag = false;
						i++;
						break;
					}
					else
					{
						i++;
					}
				}
				if (flag)
				{
					return true;
				}
				else
				{
					flag = true;
				}
			}
			i++;
		}
		return false;
	}
	static char* strConcatenateForIDs(const char* str1, char* str2)
	{
		int size1 = strlen(str1);
		int size2 = strlen(str2);

		char* res = new char[size1+size2+1];
		int i = 0,j=0;

		while (str1[i] != '\0')
		{
			res[i] = str1[j];
			j++;
			i++;
		}

		j = 0;

		while (str2[j] != '\0')
		{
			res[i] = str2[j];
			i++;
			j++;
		}
		res[i] = '\0';
		return res;
		
	}
	static void strConcatenate(char* _res, const char* c1, const char* c2)
	{
		int i = 0;
		for (i = 0; c1[i] != '\0'; i++)
		{
			_res[i] = c1[i];
		}
		_res[i] = ' ';
		i++;

		int j = 0;
		for (i, j; c2[j] != '\0'; j++, i++)
		{
			_res[i] = c2[j];
		}
		_res[i] = '\0';

	}
	static void skipLine(ifstream& fin, int totalLines)//skip 'n' lines
	{
		int bufferSize = 120;
		char* buffer = new char[bufferSize];
		for (int i = 0; i < totalLines; i++)
			fin.getline(buffer, bufferSize);
		delete[] buffer;
	}
	static char* getStringFromBuffer(const char* _buffer)
	{
		int size = strlen(_buffer);
		char* temp = new char[size + 1];
		strCopy(temp, _buffer);
		return temp;
	}
	static bool strCompare(const char*lhs, const char*rhs)
	{
		if (strlen(lhs) == strlen(rhs))
		{
			for (int i = 0; rhs[i] != '\0'; i++)
			{
				if (lhs[i] != rhs[i])
					return false;

			}
			return true;
		}
		else
		{
			return false;
		}

	}
};

class Object//Abstract Class
{
private:
	char* idPtr;
public:
	Object();
	bool CompareID(const char*);  //compare two idPtrs

	//setters and getters
	void SetID(const char*);
	char* GetID();

	//virtual functions
	virtual ~Object();

	virtual void Print() = 0;   //Pure virtual function, print function for derived classes
	virtual char* GetName();//to get username, pagetitle, ID
};
class Date
{
private:
	int day;
	int month;
	int year;
public:
	Date();
	void Print();
	void SetDate(int, int, int);//setter

								
	friend ostream& operator<<(ostream&, Date&);//overloaded operator
	bool operator<=(Date&);//to compare two date objects for latest posts of current date and previous day's date
	Date& operator=(Date&);//assignment operator

	//static
	static Date systemDate;//current date of system
	static void PrintSystemDate();
	static void setSystemDate(int, int, int);
};
class User : public Object 
{
private:
	char* namePtr;
	Post** timelinePtr;
	char** friendIDsPtr;
	User** friendListPtr;
	Page** likedPagesPtr;

	int postsCount;
	int friendsCount;
	int pagesCount;
public:
	User();
	~User();

	char* CreateNewID();//creates new id for new user
	void PrintName();
	void PrintNameWithID();
	void PrintAllPosts();//for timeline purpose
	void SetPostsPtrAndPostsCount(Post*);
	void setPagesCount(int );
	int GetPagesCount();
	User**& GetFriendListPtr();
	void LoadAUserWithoutPages(ifstream&);//for single user upto friends data, not of page data
	void ViewHome();
	void PrintLatestPosts();//in accordance with date scenario
	void Print();///prints timeline of user
	void ViewLikedPages();
	void SharePost(Post*);
	void ViewFriendList();
	void Likepage(Page*);//adds page to likepages
	void AddAFriend(User*, int);
	void SearchInUserClass(const char*);// search a substring

	//getters
	int GetFriendsCount();
	int GetPostsCount();
	char* GetName();
	char** GetFriendIDsPtr();
	Page**& GetLikedPagesPtr();
	void SetLikedPagesPtr(Page** store);

};
class Page : public Object 
{
private:
	char* titlePtr;
	int postCount;
	//int likesCount;
	Post** timelinePtr;

public:
	Page();
	~Page();

	void PrintTitleWithID();
	char* CreateNewID();
	
	void Print();//prints timeline of a page
	void LoadAPage(ifstream&);
	void PrintAllPosts();//for timeline of page
	void SetPostsPtrAndPostsCount(Post*);
	void PrintLatestPosts();// for home page of user
	void SearchInPageClass(const char*);
	void SetName(const char*);
	char* GetName();

};
class Post :public Object 
{
private:
	char* descriptionPtr;

	Object* postedByPtr;
	Object** likedByPtr;
	Comment** commentsOnAPostPtr;

	Date postDate;

	int likesCount;
	int commentsCount;

public:
	Post();
	~Post();
	bool DateCheck();//matche date with current and previous dayto print homempage
	char* CreateNewID();//for new post
	void SetPostedBy(Object* );
	void PrintPostDescriptionWithID();
	Date GetPostDate();
	char*& GetDescriptionPtr();
	int& GetLikesCount();
	int GetCommentsCount();
	Object**& GetLikedByPtr();
	void SetCommentID(Comment* cmt);
	void SetPostDate(int, int, int);
	Comment**& GetCommentsOnAPostPtr();//return Comment**
	void Print();//print posts with comments and names
	void LikePost(Object*);
	void AddCommentOnPost(const char*);
	Post(Post&);//copyConstructor
	Post& operator=(const Post&);//assignment operator for sharing purposes
	void SetLikedByPtr(Object*);
	void PrintLikedByList();
	void SearchInPostClass(const char*);// to search a substring
};
class Comment :public Object 
{
private:
	char* descriptionPtr;
	Object* commentedByPtr;
	Post* commentedOnPtr;

public:
	Comment();
	Comment(const char* caption, Object* a, Post* p);
	~Comment();
	char* CreateNewID();//for new comment
	
	void LoadCommentDescription(const char*);
	void Print();//print name/title of user/page who posted + description
	 //setters
	void SetCommentBy(Object*);
	void SetCommentOn(Post*);
};
class FastBook
{
private:
	//non static functions
	User **usersOfFb;
	Page **pagesOfFb;
	Post **postsOfFb;

	//static functions
	static User *currentUser;
	static int usersCount;
	static int pagesCount;
	static int postsCount;
	static int commentsCount;

public:

	FastBook();
	~FastBook();

	void LoadAndLinkAllData();
	void SetCurrentUser(const char*);
	void SetSystemDate(int,int,int);
	void ViewPost(const char*);
	void ViewPage(const char*);
	void ViewFriendList(const char*);
	void SharePost(const char*);
	void LikePost(const char*);
	void CommentOnPost(const char*, const char*);
	void ViewLikeList(const char*);
	void SearchString(const char*);
	void RunRemainingFunctionalities();

	//static getters
	static User* GetCurrentUser();
	static int GetPagesCount();
	static int GetPostsCount();
	static int GetUsersCount();
	static int GetCommentsCount();

	//non static getters
	User**& GetUsersOfFb();
	Page**& GetPagesOfFb();
	Post**& GetPostsOfFb();

};

//initiliazation of static variables in Global Scope
int FastBook::postsCount = 0;
int FastBook::pagesCount = 0;
int FastBook::commentsCount = 0;
int FastBook::usersCount = 0;
User* FastBook::currentUser = nullptr;
Date Date::systemDate;

//main function
int main()
{
	FastBook fb;
	fb.LoadAndLinkAllData();
	fb.RunRemainingFunctionalities();

	system("pause");
}

//definitions of class functions
FastBook::FastBook()
{
	usersOfFb = nullptr;
	pagesOfFb = nullptr;
	postsOfFb = nullptr;
}

FastBook::~FastBook()
{
	if (usersOfFb)
	{
		for (int i = 0; i < usersCount; i++)
		{
			if (usersOfFb[i])
			{
				delete[] usersOfFb[i];
			}
		}
		delete[] usersOfFb;
	}
	usersOfFb = nullptr;

	if (pagesOfFb)
	{
		for (int i = 0; i < pagesCount; i++)
		{
			if (pagesOfFb[i])
			{
				delete[] pagesOfFb[i];
			}
		}
		delete[] pagesOfFb;
	}
	pagesOfFb = nullptr;

	if (postsOfFb)
	{
		delete[] postsOfFb;
	}
	postsOfFb = nullptr;
}

void FastBook::LoadAndLinkAllData()
{
	ifstream fin;
	int bufferSize = 120, temp = 0;
	char* buffer = new char[bufferSize];

	//Loading Pages
	fin.open("myPages.txt");
	if (fin.is_open())
	{
		fin >> temp;
		pagesCount = temp;
		Helper::skipLine(fin, 3);

		if (pagesCount > 0)
		{
			pagesOfFb = new Page *[pagesCount];

			for (int i = 0; i < pagesCount; i++)
			{
				pagesOfFb[i] = new Page;
				pagesOfFb[i]->LoadAPage(fin);
			}
		}
		fin.close();
	}
	else
		cout << "Error opening PAGES file\n";

	//Loading Users
	fin.open("myUsers.txt");
	if (fin.is_open())
	{
		fin >> temp;
		usersCount = temp;
		do
		{
			fin >> buffer;
		} while (strcmp(buffer, "<-1>")!=0);
		do
		{
			fin >> buffer;
		} while (strcmp(buffer, "<-1>") != 0);

		if (usersCount > 0)
		{
			usersOfFb = new User *[usersCount];
			for (int i = 0; i < usersCount; i++)
			{
				usersOfFb[i] = new User;
				usersOfFb[i]->LoadAUserWithoutPages(fin);

				//for Liked Pages
				fin >> buffer;
				if (strcmp(buffer,"-1")!=0)
				{
					usersOfFb[i]->GetLikedPagesPtr() = new Page *[10];

					for (int m = 0; m < 10; m++)
					{
						usersOfFb[i]->GetLikedPagesPtr()[m] = nullptr;
					}

					
					usersOfFb[i]->setPagesCount(0);

					while ((strcmp(buffer,"-1") !=0))
					{
						for (int j = 0; j < pagesCount; j++)
						{
							if (pagesOfFb[j]->CompareID(buffer))
							{
								usersOfFb[i]->Likepage(pagesOfFb[j]); //for addition of like page in user's list
								break;
							}
						}
						fin >> buffer;
					}
				}//end of one page load function

				Helper::skipLine(fin, 1);
			}
			fin.close();
		}

	}
	else
		cout << "Error opening USERS file\n";

	//Associating Friends
	//------------------------------------------------------
	char** friendsTemp = nullptr;

	for (int p = 0; p < usersCount; p++)//for all users
	{
		friendsTemp = usersOfFb[p]->GetFriendIDsPtr();
		if (usersOfFb[p]->GetFriendsCount()>0)
		{
			for (int h = 0; h < usersOfFb[p]->GetFriendsCount(); h++)//for all char friends of pth user	
			{
				if (h == 0)
				{
					usersOfFb[p]->GetFriendListPtr() = new User*[10];

					for (int u = 0; u < 10; u++)
					{
						usersOfFb[p]->GetFriendListPtr()[u] = nullptr;
					}
				}
				
				for (int r = 0; r < usersCount ; r++)//for all users objects created
				{
					if (usersOfFb[r]->CompareID(friendsTemp[h]))
					{
						usersOfFb[p]->AddAFriend(usersOfFb[r], h);//add rth user as a friend in friendlist of pth user
						break;
					}
				}
			}
		}
	}
	//------------------------------------------------------

	//Loading Posts
	fin.open("myPosts.txt");
	if (fin.is_open())
	{
		fin >> temp;
		postsCount = temp;
		Helper::skipLine(fin, 8);

		if (postsCount > 0)
		{
			postsOfFb = new Post *[postsCount];
			for (int i = 0; i < postsCount; i++)
			{
				if (i == 0)
				{
					for (int i = 0; i < postsCount; i++)
					{
						postsOfFb[i] = nullptr;
					}
				}
				postsOfFb[i] = new Post;
				//-------------
				int d = 0, m = 0, y = 0;
				fin.getline(buffer, bufferSize);
				postsOfFb[i]->SetID(buffer);

				fin >> d;
				fin >> m;
				fin >> y;
				postsOfFb[i]->SetPostDate(d, m, y);

				Helper::skipLine(fin, 1);

				fin.getline(buffer, bufferSize);

				postsOfFb[i]->GetDescriptionPtr() = Helper::getStringFromBuffer(buffer);

				fin >> buffer;
				if (strcmp(buffer, "-1") != 0)// i.e post has some like/likes
				{
					postsOfFb[i]->GetLikesCount() = 0;

					while (strcmp(buffer, "-1") != 0)  //getting likes from post's file 
					{
						if (postsOfFb[i]->GetLikesCount() == 0)
						{
							postsOfFb[i]->GetLikedByPtr() = new Object*[10];
							for (int h = 0; h < 10; h++)
							{
								postsOfFb[i]->GetLikedByPtr()[h] = nullptr;
							}
						}
						
						if (buffer[0] == 'u')//searching in users
						{
							for (int k = 0; k < usersCount; k++)
							{
								if (usersOfFb[k]->CompareID(buffer))
								{
									postsOfFb[i]->SetLikedByPtr(usersOfFb[k]);
									break;
								}
							}
						}
						if (buffer[0] == 'p')//searching in pages
						{
							for (int l = 0; l < pagesCount; l++)
							{
								if (pagesOfFb[l]->CompareID(buffer))
								{
									postsOfFb[i]->SetLikedByPtr(pagesOfFb[l]);
									break;
								}
							}
						}
						fin >> buffer;
					}
				}
				//-------------
				Helper::skipLine(fin, 1);

				fin.getline(buffer, 120);//to set posted by (user or page)
				if (buffer[0] == 'u')//searching in users
				{
					for (int k = 0; k < usersCount; k++)
					{
						if (usersOfFb[k]->CompareID(buffer))
						{
							postsOfFb[i]->SetPostedBy(usersOfFb[k]);
							usersOfFb[k]->SetPostsPtrAndPostsCount(postsOfFb[i]);
							break;
						}
					}
				}
				if (buffer[0] == 'p')//searching in pages
				{
					for (int l = 0; l < pagesCount; l++)
					{
						if (pagesOfFb[l]->CompareID(buffer))
						{
							postsOfFb[i]->SetPostedBy(pagesOfFb[l]);
							pagesOfFb[l]->SetPostsPtrAndPostsCount(postsOfFb[i]);
							break;
						}
					}
				}
				
				Helper::skipLine(fin, 1);
			}
		}
		fin.close();
	}
	else
		cout << "Error opening POSTS file\n";

	//Loading Comments
	fin.open("myComments.txt");
	if (fin.is_open())
	{
		fin >> temp;
		commentsCount = temp;
		Helper::skipLine(fin, 3);

		if (commentsCount > 0)
		{
			for (int i = 0; i < commentsCount; i++)
			{
				Comment *newComment = new Comment;

				//input ID of Comment
				fin >> buffer;
				newComment->SetID(buffer);

				//input post address on which comment is posted
				fin >> buffer;
				for (int j = 0; j < postsCount; j++) //finding jth post for newComment
				{
					if (postsOfFb[j]->CompareID(buffer))
					{
						if (postsOfFb[j]->GetCommentsCount() == 0) //for first time of iteration, it will allocated memory
						{
							postsOfFb[j]->GetCommentsOnAPostPtr() = new Comment*[10];
							for (int h = 0; h < 10; h++)
							{
								postsOfFb[j]->GetCommentsOnAPostPtr()[h] = nullptr;
							}
						}
						newComment->SetCommentOn(postsOfFb[j]);
						postsOfFb[j]->SetCommentID(newComment);
						break;
					}
				}

				//input user/page who commented
				fin >> buffer;

				if (buffer[0] == 'u')
				{
					for (int s = 0; s < usersCount; s++)
					{
						if (usersOfFb[s]->CompareID(buffer))
						{
							newComment->SetCommentBy(usersOfFb[s]);
							break;
						}
					}
				}
				else if (buffer[0] == 'p')
				{
					for (int f = 0; f < pagesCount; f++)
					{
						if (pagesOfFb[f]->CompareID(buffer))
						{
							newComment->SetCommentBy(pagesOfFb[f]);
							break;
						}
					}
				}

				fin.ignore();
				fin.getline(buffer, bufferSize);
				newComment->LoadCommentDescription(buffer);
			}
			fin.close();
		}
	}
	else
		cout << "Error opening COMMENT file\n";

	delete[] buffer;
	//---------------------------Filing & Association Ended-------------------------------
}

void FastBook::SetCurrentUser(const char * address)
{
	cout << "------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tSet Current User to (" << address << ")" << endl << endl;
	if(address[0]=='u')
	{
		for (int i = 0; i < usersCount; i++)
		{
			if (strcmp(usersOfFb[i]->GetID(), address) == 0)
			{
				currentUser = usersOfFb[i];
				cout << currentUser->GetName() << " successfully set as Current User of FastBook\n";
				break;
			}
		}
	}
}

void FastBook::SetSystemDate(int d, int m,int y)
{
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << "Set System Date to "<<d<<" "<<m<<" "<<y<<"\n";
	Date::setSystemDate(d,m,y);
	cout << "System Date:\t";
	Date::systemDate.PrintSystemDate();
	cout << endl;
}

void FastBook::ViewPost(const char *id)
{
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tView Post (" << id << ")" << endl << endl;

	for (int i = 0; i < postsCount; i++)
	{
		if (postsOfFb[i]->CompareID(id))
		{
			postsOfFb[i]->Print();
			break;
		}
	}
}

void FastBook::ViewPage(const char *id)
{
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tView Page (" << id << ")\n\n";
	for (int i = 0; i < pagesCount; i++)
	{
		if (pagesOfFb[i]->CompareID(id))
		{
			pagesOfFb[i]->Print();// print page's timeline
			break;
		}
	}
}

void FastBook::ViewFriendList(const char *id)
{
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tView Friend List (" << id << ")" << endl << endl;
	for (int i = 0; i < usersCount; i++)
	{
		if (usersOfFb[i]->CompareID(id))
		{
			usersOfFb[i]->ViewFriendList();
			break;
		}
	}
}

void FastBook::SharePost(const char *id)
{
	cout << "-------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tShare Post ("<<id<<")\n";
	if (currentUser->GetPostsCount() < 10)
	{
		for (int i = 0; i < postsCount; i++)
		{
			if (postsOfFb[i]->CompareID(id))
			{
				currentUser->SharePost(postsOfFb[i]);
				break;
			}
		}
	}
	else
	{
		cout << "Error:	Post Share Limit Reached.\n";
	}
}


void FastBook::LikePost(const char * id)
{
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tLike Post (" << id << ")" << endl << endl;
	for (int i = 0; i < postsCount; i++)
	{
		if (strcmp(id, postsOfFb[i]->GetID()) == 0)  
		{
			postsOfFb[i]->LikePost(currentUser);
			break;
		}
	}
}

void FastBook::CommentOnPost(const char * postId, const char * cmnt)
{
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tPost Comment (" << postId << " , " << cmnt << ")\n";
	for (int i = 0; i < postsCount; i++)
	{
		if (postsOfFb[i]->CompareID(postId))
		{
			postsOfFb[i]->AddCommentOnPost(cmnt);
			break;
		}
	}
}

void FastBook::ViewLikeList(const char * add)
{
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tView Like List (" << add << ")\n\n";
	for (int i = 0; i < postsCount; i++)
	{
		if (postsOfFb[i]->CompareID(add))
		{
			postsOfFb[i]->PrintLikedByList();
			break;
		}
	}
}

void FastBook::SearchString(const char * str)
{
	cout << "--------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tSearch (" << str << ")\n\n";
	cout << "Users:\n";
	for (int x = 0; x < usersCount; x++)
	{
		usersOfFb[x]->SearchInUserClass(str);
	}

	cout << "Posts:\n";
	for (int x = 0; x < postsCount; x++)
	{
		postsOfFb[x]->SearchInPostClass(str);
	}

	cout << "Pages:\n";
	for (int x = 0; x < pagesCount; x++)
	{
		pagesOfFb[x]->SearchInPageClass(str);
	}

}

void FastBook::RunRemainingFunctionalities()
{
	//demanded functionalities
	SetCurrentUser("u7");
	SetSystemDate(15,11,2017);

	currentUser->ViewFriendList();
	currentUser->ViewLikedPages();
	currentUser->ViewHome();
	currentUser->Print();//over rided function to prints timeline of user/page

	ViewLikeList("post5");
	LikePost("post5");
	ViewLikeList("post5");
	CommentOnPost("post4", "Good Luck for your Result.");
	ViewPost("post4");
	SharePost("post5");

	currentUser->Print();//over rided function to prints timeline of user/page
	ViewPage("p1");

	SearchString("Birthday");
	SearchString("Ali");
}

Object::Object()
{
	idPtr = nullptr;
}

Object::~Object()
{
	if (idPtr)
		delete[] idPtr;
	idPtr = nullptr;
}

bool Object::CompareID(const char * temp)
{
	return Helper::strCompare(idPtr, temp);
}

void Object::SetID(const char * rhs)
{
	idPtr = Helper::getStringFromBuffer(rhs);
}

char * Object::GetName()
{
	return idPtr;
}

Date::Date()
{
	day = month = year = 0;
}

void Date::Print()
{
	cout << "(" << day << "/" << month << "/" << year << ")";
}

void Date::SetDate(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
}

bool Date::operator<=(Date &rhs)
{
	if (day == rhs.day || day == rhs.day - 1)
	{
		if (month == rhs.month)
		{
			if (year == rhs.year)
			{
				return true;
			}
		}
	}
	return false;
}

Date & Date::operator=(Date &rhs)
{
	if (this != &rhs)
	{
		day = rhs.day;
		month = rhs.month;
		year = rhs.year;
	}
	return *this;
}

void Date::PrintSystemDate()
{
	cout << "(" << systemDate.day << "/" << systemDate.month << "/" << systemDate.year << ")";
}

void Date::setSystemDate(int d, int m, int y)
{
	systemDate.day = d;
	systemDate.month = m;
	systemDate.year = y;
}

ostream & operator<<(ostream &out, Date &rhs)
{
	out << rhs.day << "/" << rhs.month << "/" << rhs.year << endl;
	return out;
}

User::User()
{
	namePtr = nullptr;
	timelinePtr = nullptr;
	friendIDsPtr = nullptr; 
	friendListPtr = nullptr;
	likedPagesPtr = nullptr;

	postsCount = 0;
	friendsCount = 0;
	pagesCount = 0;
}

User::~User()
{
	if (namePtr)
		delete[] namePtr;
	namePtr = nullptr;

	if (timelinePtr)
	{
		for (int i = 0; i < postsCount; i++)
		{
			if (timelinePtr[i])
				delete[] timelinePtr[i];
		}
		delete[] timelinePtr;
	}
	timelinePtr = nullptr;

	if (friendListPtr)
	{
		delete[] friendListPtr;
	}
	friendListPtr = nullptr;

	if (friendIDsPtr)
	{
		for (int i = 0; i < friendsCount; i++)
		{
			if (friendIDsPtr[i])
				delete[] friendIDsPtr[i];
		}
		delete[] friendIDsPtr;
	}
	friendIDsPtr = nullptr;

	if (likedPagesPtr)
	{
		delete[] likedPagesPtr;
	}
	likedPagesPtr = nullptr;

}

char * User::CreateNewID()
{
	
		int digits = Helper::calculateNumberOfDigits(FastBook::GetUsersCount()+1);

		int size1 = strlen("u");

		char* res = nullptr;
		char* num = new char[digits + 1];
		_itoa(FastBook::GetUsersCount()+1, num, 10);
		res = Helper::strConcatenateForIDs("u", num);
		if (num)
		{
			delete[] num;
		}
		num = nullptr;

		return res;
}

void User::LoadAUserWithoutPages(ifstream &fin)
{
	int bufferSize = 120;
	char* buffer = new char[bufferSize];
	char* buffer1 = new char[bufferSize];
	int temp = 0;
	fin >> buffer;
	SetID(buffer);

	//to set first and last name together
	fin >> buffer;
	fin >> buffer1;
	namePtr = new char[strlen(buffer) + strlen(buffer1) + 2]; //2 extra i.e 1st for '\0' and 2nd for ' ' between first and last names
	Helper::strConcatenate(namePtr, buffer, buffer1);
	delete[] buffer1;
	buffer1 = nullptr;

	//fin.ignore();
	fin >> buffer;
	//fin >> buffer;
	if (strcmp(buffer, "-1") != 0) 
	{
		friendsCount = 0;
		friendIDsPtr = new char*[10];
		for (int i = 0; i < 10; i++)
		{
			friendIDsPtr[i] = nullptr;
		}

		//for friends
		while (strcmp(buffer, "-1") != 0)
		{
			friendIDsPtr[friendsCount] = Helper::getStringFromBuffer(buffer);
			++friendsCount;
			fin >> buffer;
		}
	}
	delete[] buffer;
}

void User::ViewHome()
{
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tView Home\n\n";
	cout << namePtr<< "----HOME---\n\n";
	//calling print functions of posts of friends of user for date less than or equal to system date
	for (int i = 0; i < friendsCount; i++)
	{
		friendListPtr[i]->PrintLatestPosts();
	}

	for (int j = 0; j < pagesCount; j++)
	{
		likedPagesPtr[j]->PrintLatestPosts();
	}

}

Post::Post()
{
	descriptionPtr = nullptr;
	postedByPtr = nullptr;
	likedByPtr = nullptr;
	commentsOnAPostPtr = nullptr;


	likesCount = 0;
	commentsCount = 0;
}

bool Post::DateCheck()
{
	if (postDate <= Date::systemDate)
	{
		return true;
	}
	else
	{
		return false;
	}

}

char * Post::CreateNewID()
{
		int digits = Helper::calculateNumberOfDigits(FastBook::GetPostsCount()+1);

		int size1 = strlen("post");

		char* num = new char[digits + 1];
		_itoa(FastBook::GetPostsCount()+1, num, 10);
		char* res = Helper::strConcatenateForIDs("post", num);
		if (num)
		{
			delete[] num;
		}
		num = nullptr;

		return res;
}

void Post::SetPostedBy(Object *temp)
{
	postedByPtr = temp;
}

Post::~Post()
{
	if (descriptionPtr)
		delete[] descriptionPtr;
	descriptionPtr = nullptr;

	postedByPtr = nullptr;

	if (likedByPtr)
	{
		delete[] likedByPtr;
	}
	likedByPtr = nullptr;

	if (commentsOnAPostPtr)
	{
		for (int i = 0; i < commentsCount; i++)
		{
			if (commentsOnAPostPtr[i])
				delete[] commentsOnAPostPtr[i];
		}
		delete[] commentsOnAPostPtr;
	}
	commentsOnAPostPtr = nullptr;
}

void User::PrintLatestPosts()
{
	for (int j = 0; j < postsCount; j++)
	{
		if (timelinePtr[j]->DateCheck())
		{
			timelinePtr[j]->Print();
		}
	}
}

void User::Print()
{
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tView TimeLine\n\n";
	PrintName();
	cout << "'s TimeLine.";
	PrintAllPosts();
}

void User::ViewLikedPages()
{
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\t View Liked Pages\n";
	cout << namePtr<<"'s Liked Pages\n";
	for (int i = 0; i < pagesCount; i++)
	{
		likedPagesPtr[i]->PrintTitleWithID();
	}
}

void User::SharePost(Post *temp)
{
	if (postsCount < 10)
	{
		if (postsCount == 0)
		{
			timelinePtr = new Post*[10];
			for (int i = 0; i < 10; i++)
			{
				timelinePtr[i] = nullptr;
			}
		}
		timelinePtr[postsCount] = new Post(*temp);
		postsCount++;
	}
	else
	{
		cout << "Error:	Post Shared Limit Reached\n";
	}
}

void User::PrintName()
{
	cout << namePtr;
}

void User::ViewFriendList()
{
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	cout << "Command:\tView Friend List (";
	PrintName();
	cout << ")\n";
	for (int i = 0; i < friendsCount; i++)
	{
		friendListPtr[i]->PrintNameWithID();
		cout << endl;
	}
}

void User::Likepage(Page *address)
{
	if (pagesCount < 10 && pagesCount>=0)
	{
		likedPagesPtr[pagesCount] = address;
		pagesCount++;
	}
	else
	{
		cout << "Error:\tLikes Limit Reached\n";
	}
}

void User::AddAFriend(User * userAddress, int index)
{
	friendListPtr[index] = userAddress;
}

void User::SearchInUserClass(const char *str)
{
	if (Helper::strFind(GetName(), str))
	{
		PrintNameWithID();
		cout << endl;
	}
}

char * User::GetName()
{
	return namePtr;
}

void Post::Print()
{
	cout <<"\n"<< postedByPtr->GetName() << " shared " << descriptionPtr << "\t";
	postDate.Print();
	cout << endl;

	//comments
	for (int i = 0; i < commentsCount; i++)
	{
		cout << "\t";
		commentsOnAPostPtr[i]->Print();
		cout << endl;
	}
	cout << "\t\t\t-----------------------------------------\n";
}

void Post::LikePost(Object * obj)
{
	if (likesCount < 10)
	{
		if (likesCount == 0)
		{
			likedByPtr = new Object*[10];
			for (int i = 0; i < 10; i++)
			{
				likedByPtr[i] = nullptr;
			}
		}
		likedByPtr[likesCount] = obj;
		++likesCount;
	}
	else
	{
		cout << "Error:	Likes Limit Reached\n";
	}
}

void Post::AddCommentOnPost(const char * cmnt)
{
	if (commentsCount < 10)
	{
		Comment* temp = new Comment(cmnt, FastBook::GetCurrentUser(), this);
		temp->SetID(temp->CreateNewID());
		commentsOnAPostPtr[commentsCount] = temp;
		commentsCount++;
	}
	else
	{
		cout << "Error:	Comments Limit Reached\n";
	}
}

Post::Post(Post &rhs)
{
	SetID(CreateNewID());
	descriptionPtr = Helper::getStringFromBuffer(rhs.descriptionPtr);
	postedByPtr = FastBook::GetCurrentUser();
	likedByPtr = nullptr;
	commentsOnAPostPtr = nullptr;
	postDate = Date::systemDate;

	likesCount = 0;
	commentsCount = 0;
}

Post & Post::operator=(const Post &rhs)
{
	if (this != &rhs)
	{
		SetID(CreateNewID());
		descriptionPtr = Helper::getStringFromBuffer(rhs.descriptionPtr);
		postedByPtr = FastBook::GetCurrentUser();
		likedByPtr = nullptr;
		commentsOnAPostPtr = nullptr;
		postDate = Date::systemDate;

		likesCount = 0;
		commentsCount = 0;
	}
	return *this;
}

void Post::SetLikedByPtr(Object * rhs)
{
	likedByPtr[likesCount] = rhs;
	++likesCount;
}

Page::Page()
{
	titlePtr = nullptr;
	postCount = 0;
	//likesCount = 0;
	timelinePtr = nullptr;
}

Page::~Page()
{
	if (titlePtr)
		delete[] titlePtr;
	titlePtr = nullptr;

	if (timelinePtr)
	{
		for (int i = 0; i < postCount; i++)
		{
			if (timelinePtr[i])
				delete[] timelinePtr[i];
		}
		delete[] timelinePtr;
	}
	timelinePtr = nullptr;
}

void Page::Print()
{
	cout << GetName() << endl;
	PrintAllPosts();
}

void Page::LoadAPage(ifstream & read)
{
	int bufferSize = 120;
	char* buffer = new char[bufferSize];
	read >> buffer;
	SetID(buffer);

	//reading title of page
	read.ignore();
	read.getline(buffer, bufferSize);
	SetName(buffer);
	delete[] buffer;
}

void Page::PrintAllPosts()
{
	for (int j = 0; j < postCount; j++)
	{
		timelinePtr[j]->Print();
	}
}

void Page::SetPostsPtrAndPostsCount(Post *address)
{
	if (postCount == 0)
	{
		timelinePtr = new Post*[10];
		for (int i = 0; i < 10; i++)
		{
			timelinePtr[i] = nullptr;
		}
	}

	timelinePtr[postCount] = address;
	++postCount;
}

void Page::PrintLatestPosts()
{
	for (int j = 0; j < postCount; j++)
	{
		if (timelinePtr[j]->DateCheck())
		{
			timelinePtr[j]->Print();
		}
	}
}

void Page::SearchInPageClass(const char *str)
{
	if (Helper::strFind(GetName(), str))
	{
		PrintTitleWithID();
	}
}

void Page::SetName(const char * buffer)
{
	titlePtr = Helper::getStringFromBuffer(buffer);
}

char * Page::GetName()
{
	return titlePtr;
}

Comment::Comment()
{
	descriptionPtr = nullptr;
	commentedByPtr = nullptr;
	commentedOnPtr = nullptr;
}

Comment::~Comment()
{
	if (descriptionPtr)
		delete[] descriptionPtr;
	descriptionPtr = nullptr;

	commentedByPtr = nullptr;

	commentedOnPtr = nullptr;
}

char * Comment::CreateNewID()
{
		int digits = Helper::calculateNumberOfDigits(FastBook::GetCommentsCount()+1);
		int size1 = strlen("c");

		char* num = new char[digits + 1];
		_itoa(FastBook::GetCommentsCount()+1, num, 10);
		char* res = Helper::strConcatenateForIDs("c", num);
		if (num)
		{
			delete[] num;
		}
		num = nullptr;

		return res;
}


void Comment::LoadCommentDescription(const char *buffer)
{
	descriptionPtr = Helper::getStringFromBuffer(buffer);
}

void Comment::Print()
{
	cout << commentedByPtr->GetName() << " wrote:\t\t" << descriptionPtr ;
}

void Comment::SetCommentBy(Object * add)
{
	commentedByPtr = add;
}

void Comment::SetCommentOn(Post * add)
{
	commentedOnPtr = add;
}

void Post::PrintLikedByList()
{
	for (int i = 0; i < likesCount; i++)
	{
		cout << likedByPtr[i]->GetName() << endl;
	}
}

void Post::SearchInPostClass(const char *str)
{
	if (Helper::strFind(descriptionPtr, str))
	{
		PrintPostDescriptionWithID();
	}
}

User * FastBook::GetCurrentUser()
{
	return currentUser;
}

int FastBook::GetPagesCount()
{
	return pagesCount;
}

int FastBook::GetCommentsCount()
{
	return commentsCount;
}

int FastBook::GetPostsCount()
{
	return postsCount;
}

int FastBook::GetUsersCount()
{
	return usersCount;
}

char* Object::GetID()
{
	return idPtr;
}

void User::PrintNameWithID()
{
	cout << "---" << GetID() << "-"<<GetName();
}

void User::PrintAllPosts()
{
	for (int j = 0; j < postsCount; j++)
	{
		timelinePtr[j]->Print();
	}
}

void User::SetPostsPtrAndPostsCount(Post *address)
{
	if (postsCount == 0)
	{
		timelinePtr = new Post*[10];
		for (int i = 0; i < 10; i++)
		{
			timelinePtr[i] = nullptr;
		}
	}
	timelinePtr[postsCount] = address;
	++postsCount;
}

void User::setPagesCount(int n)
{
	pagesCount = n;
}

int User::GetPagesCount()
{
	return pagesCount;
}

User**& User::GetFriendListPtr()
{
	return friendListPtr;
}

int User::GetFriendsCount()
{
	return friendsCount;
}

int User::GetPostsCount()
{
	return postsCount;
}

char** User::GetFriendIDsPtr()
{
	return friendIDsPtr;
}

Page**& User::GetLikedPagesPtr()
{
	return likedPagesPtr;
}

void User::SetLikedPagesPtr(Page** store)
{
	likedPagesPtr = store;
}

void Page::PrintTitleWithID()
{
	cout << "---" << GetID() << "-" << titlePtr << endl;
}

char * Page::CreateNewID()
{
		int digits = Helper::calculateNumberOfDigits(FastBook::GetPagesCount()+1);
		int size1 = strlen("p");

		char* res = nullptr;
		char* num = new char[digits + 1];
		_itoa(FastBook::GetPagesCount()+1, num, 10);
		res = Helper::strConcatenateForIDs("p", num);

		if (num)
		{
			delete[] num;
		}
		num = nullptr;

		return res;	
}

void Post::PrintPostDescriptionWithID()
{
	cout << "---" << GetID() << "-";
	cout << postedByPtr->GetName() << " shared " << descriptionPtr << endl;
}

Date Post::GetPostDate()
{
	return postDate;
}

char *& Post::GetDescriptionPtr()
{
	return descriptionPtr;
}

int & Post::GetLikesCount()
{
	return likesCount;
}

int Post::GetCommentsCount()
{
	return commentsCount;
}

Object **& Post::GetLikedByPtr()
{
	return likedByPtr;
}

void Post::SetCommentID(Comment* cmt)
{
	if (commentsCount == 0)
	{
		commentsOnAPostPtr = new Comment*[10];
		for (int i = 0; i < 10; i++)
		{
			commentsOnAPostPtr[i] = nullptr;
		}
	}

	commentsOnAPostPtr[commentsCount] = cmt;
	++commentsCount;
}

void Post::SetPostDate(int d, int m, int y)
{
	postDate.SetDate(d, m, y);
}

Comment**& Post::GetCommentsOnAPostPtr()
{
	return commentsOnAPostPtr;
}

Comment::Comment(const char* caption, Object* a, Post* p)
{
	descriptionPtr = Helper::getStringFromBuffer(caption);
	commentedByPtr = a;
	commentedOnPtr = p;
}

User**& FastBook::GetUsersOfFb()
{
	return usersOfFb;
}

Page**& FastBook::GetPagesOfFb()
{
	return pagesOfFb;
}

Post**& FastBook::GetPostsOfFb()
{
	return postsOfFb;
}