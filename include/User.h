#ifndef USER_H
#define USER_H
#include <string>

class User
{
    public:
        User(std::string login, std::string password);
        User(int id, std::string login, std::string password);
        std::string getLogin();
        void setLogin(std::string val);
        std::string getPassword();
        void setPassword(std::string val);
        int getNextId();
        int getId();

    protected:

    private:
        int id;
        static int nextId;
        std::string login;
        std::string password;
        void setId(int val);
};

#endif // USER_H
