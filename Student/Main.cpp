//  Demo 

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <format>
#include <cstdint>
#include <vector>
#include <algorithm>

namespace studentManager {

    using Number = unsigned short;
    constexpr std::string_view Filename = "D:\\Student.bin";
    constexpr std::string_view tempFilename = "D:\\Studenttemp.bin";

    constexpr enum class StudentSituation : uint8_t { Fired, Waiting, Active, Transferd, Educated, All };
    constexpr enum class RecordSituation : uint8_t { Erased, Active, All };

    class Student {
    public:
        Student() = default;

        Student(std::string name, Number id, Number age, std::map<std::string, float> books)
            : m_Name(std::move(name)), m_ID(id), m_Age(age), BookScore(std::move(books)) {
            CalculateGrade();
            m_StudentSituation = StudentSituation::Active;
            m_RecordSituation = RecordSituation::Active;
        }

        void CalculateGrade() {
            float sum = 0;
            for (const auto& [_, score] : BookScore)
                sum += score;

            m_Grade = BookScore.empty() ? 0 : sum / BookScore.size();
        }

        void Serialize(std::ofstream& os) const {
            WriteString(os, m_Name);
            os.write(reinterpret_cast<const char*>(&m_ID), sizeof(m_ID));
            os.write(reinterpret_cast<const char*>(&m_Age), sizeof(m_Age));
            os.write(reinterpret_cast<const char*>(&m_Grade), sizeof(m_Grade));

            

            auto s = static_cast<uint8_t>(m_StudentSituation);
            os.write(reinterpret_cast<const char*>(&s), sizeof(s));
            s = static_cast<uint8_t>(m_RecordSituation);
            os.write(reinterpret_cast<const char*>(&s), sizeof(s));

            size_t mapSize = BookScore.size();
            os.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));
            for (const auto& [key, val] : BookScore) {
                WriteString(os, key);
                os.write(reinterpret_cast<const char*>(&val), sizeof(val));
            }
        }

        void Deserialize(std::ifstream& is) {
            m_Name = ReadString(is);
            is.read(reinterpret_cast<char*>(&m_ID), sizeof(m_ID));
            is.read(reinterpret_cast<char*>(&m_Age), sizeof(m_Age));
            is.read(reinterpret_cast<char*>(&m_Grade), sizeof(m_Grade));

            uint8_t s;
            is.read(reinterpret_cast<char*>(&s), sizeof(s));
            m_StudentSituation = static_cast<StudentSituation>(s);
            is.read(reinterpret_cast<char*>(&s), sizeof(s));
            m_RecordSituation = static_cast<RecordSituation>(s);

            size_t mapSize;
 
            is.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));
            
            BookScore.clear();
            
            for (size_t i = 0; i < mapSize; ++i) {
            
                std::string key = ReadString(is);
                float val;
                
                is.read(reinterpret_cast<char*>(&val), sizeof(val));
                BookScore[key] = val;
            }// end for
        }// end function

        void Print(bool show = true) const {
            
            if (show)
                title();
            
            constexpr auto fmt = "{:<5}{:<20}{:<10}{:<10}{:<15}{:<15}{:<10}\n\n";

            std::cout << std::format(fmt,
                m_ID, m_Name, m_Age, m_Grade,
                Get_StrStudentStatus(m_StudentSituation),
                Get_StrRecordStatus(m_RecordSituation),
                1);



            for (const auto& [book, score] : BookScore)
                std::cout << std::format("[{:<20} {:<10}]\n", book, score);
            
            std::cout << "\n\n";

        }// end function

        void Set_RecordStatus(const RecordSituation &newstatus) {
            m_RecordSituation = newstatus;
        }
        void Set_StudentStatus(const StudentSituation& newstatus) {
            m_StudentSituation = newstatus;
        }

        Number GetID() const { return m_ID; }
        RecordSituation GetRecordStatus() const { return m_RecordSituation; }
        StudentSituation GetStudentStatus() const { return m_StudentSituation; }
        float Get_Grade()const {
            return m_Grade;
        }

    private:
        static void WriteString(std::ostream& os, const std::string& str) {
            size_t len = str.length();
            os.write(reinterpret_cast<const char*>(&len), sizeof(len));
            os.write(str.data(), len);
        }

        static std::string ReadString(std::istream& is) {
            size_t len;
            is.read(reinterpret_cast<char*>(&len), sizeof(len));
            std::string str;
            str.resize(len);
            is.read(str.data(), len);
            return str;
        }

        void title()const {
            constexpr auto fmt = "{:<5}{:<20}{:<10}{:<10}{:<15}{:<15}{:<10}";
            std::cout << std::format(fmt, "ID", "Name", "Age", "Grade", "StudentStatus", "RecordStatus", "Access") << '\n';
            std::cout << std::string(80, '-') << '\n';
        }

        std::string_view Get_StrRecordStatus(const RecordSituation &situation)const {
            switch (situation)
            {
            case RecordSituation::All: return "ALL";
            case RecordSituation::Active: return "Active";
            case RecordSituation::Erased: return "Erased";
            default: return "ERROR";
            }// end switch
        }//  end fucntion

        std::string_view Get_StrStudentStatus(const StudentSituation& situation)const {
            switch (situation)
            {
            case StudentSituation::All:         return "ALL";
            case StudentSituation::Active:      return "Active";
            case StudentSituation::Educated:    return "Educated";
            case StudentSituation::Fired:       return "Fired";
            case StudentSituation::Transferd:   return "Transferred";
            case StudentSituation::Waiting:     return "Waiting";
            default: return "ERROR";
            }// end switch
        }//  end fucntion


    private:

        std::string m_Name;
        Number m_ID = 0;
        Number m_Age = 0;
        float m_Grade = 0;

        std::map<std::string, float> BookScore;
        RecordSituation m_RecordSituation = RecordSituation::Active;
        StudentSituation m_StudentSituation = StudentSituation::Active;
    };

    class DataBase {
    public:
        void Save(const Student& stu) {
            std::ofstream file(Filename.data(), std::ios::binary | std::ios::app);

            if (!file)
                throw std::ios::failure("Failed to open file for writing");
            
            
            if (stu.GetID() == 0)
                return;

            stu.Serialize(file);
        }// end function

        std::vector<Student> LoadAll(StudentSituation studentFilter = StudentSituation::All,
            RecordSituation recordFilter = RecordSituation::All) const {

            std::ifstream file(Filename.data(), std::ios::binary);
            
            if (!file) 
                throw std::ios::failure("Failed to open file for reading");

            std::vector<Student> students;

            while (file.peek() != EOF) {
                Student s;
                
                s.Deserialize(file);

                if ((studentFilter == StudentSituation::All || s.GetStudentStatus() == studentFilter) &&
                    (recordFilter == RecordSituation::All || s.GetRecordStatus() == recordFilter)) {
                    students.push_back(s);
                }
            }// end while
            return students;
        }// end function
        
        auto Sort_By_grade(auto vec = LoadAll()) {
            
            std::sort(vec.begin(), vec.end(), [](const Student& a, const Student& b) {
                return a.Get_Grade() > b.Get_Grade();
                });

            return vec;
        }// end function

        void Search(const Number& ID, Student& res) {
            std::ifstream file(Filename.data(), std::ios::binary | std::ios::in);
            bool found = false;

            if (file.is_open()) {
                Student temp;

                while (file.peek() != EOF) {
                    
                    temp.Deserialize(file);
                    
                    if (temp.GetID() == ID)
                    {
                        found = true;
                        res = temp;
                        break;
                    }
                }// end while

            }// end if
            else
                throw(std::ios::failure::runtime_error("Can not open file for reading"));

            file.close();

        }// end function

        bool DeleteRecord(const Number& id) {
            std::ifstream file(Filename.data(), std::ios::binary);
            std::ofstream file2(tempFilename.data(), std::ios::binary);

            bool deleted = false;


            if (file.is_open()) {
                Student temp;

                while (file.peek() != EOF) {

                    temp.Deserialize(file);

                    if (temp.GetID() == id) {
                        temp.Set_RecordStatus(RecordSituation::Erased);
                        deleted = true;
                    }
                
                    temp.Serialize(file2);
                
                }// end while


            }
            else
                throw(std::ios::failure("Can not open file"));
            
            file.close();
            file2.close();

            if (deleted) {
                remove(Filename.data());
                rename(tempFilename.data(), Filename.data());
            }


            return deleted;
        }// end function
        
        bool StuStatus(const Number& id, const StudentSituation &newsituation) {
            
            std::ifstream file(Filename.data(), std::ios::binary);
            std::ofstream file2(tempFilename.data(), std::ios::binary);

            bool changed(false);

            if (file.is_open()) {
                Student temp;

                while (file.peek() != EOF ) {
                
                    temp.Deserialize(file);

                    if (temp.GetID() == id) {
                        temp.Set_StudentStatus(newsituation);
                        changed = true;
                    }


                    temp.Serialize(file2);

                }// end while


            }
            else
                throw(std::ios::failure("Can not open file"));


            file.close();
            file2.close();

            if (changed)
            {
                remove(Filename.data());
                rename(tempFilename.data(), Filename.data());
            }

            return changed;

        }// end fucntion
        
    };//    end class database

    namespace AdminManager {

        const std::string adminfile = "D:\\Admin.bin";
        const std::string tempadminfile = "D:\\tempAdmin.bin";              //  using temperory file for editing main file.
        constexpr enum class AccessLevel : uint8_t { NoAccess, LowAccess, FullAccess };


        class Admin {
        public:
            Admin() = default;

            Admin(const std::string_view& name, const std::string_view& pass) : m_Name(name), m_Password(pass), m_Access(AccessLevel::LowAccess) {
                
            }

            bool has_Access()const {
                if (m_Access != AccessLevel::NoAccess)
                    return true;

                return false;
            }// end function

            void Set_Accesss(const AccessLevel& newAccess) {
                m_Access = newAccess;
            }// end function

            bool Remove_Access() {
                bool removed = false;

                std::ifstream file(adminfile.data(), std::ios::binary);
                std::ofstream tempfile(tempadminfile.data(), std::ios::binary);



                if (file.is_open() and tempfile.is_open()) {
                    Admin temp;

                    while (file.peek() != EOF)
                    {
                        temp.Deserialize(file);

                        if (m_Name == temp.m_Name and m_Password == temp.m_Password) {
                            temp.m_Access = AccessLevel::NoAccess;
                            removed = true;
                        }

                        temp.Serialize(tempfile);
                    }// end while

                }
                else
                    throw(std::ios::failure("Can not open files\n"));

                file.close();
                tempfile.close();

                if (removed) {
                    remove(adminfile.data());
                    rename(tempadminfile.data(), adminfile.data());
                }

                return removed;
            }// end function

            void Save() {
                std::ofstream file(adminfile.data(), std::ios::binary);

                if (file.is_open()) {
                    Serialize(file);
                }

            }// end function

            void Read() {
                std::ifstream file(adminfile.data());

                if (file.is_open()) {
                    Deserialize(file);
                }
            }// end function

            void Print() {
                static bool show = true;
                if (show) {
                    Title();
                    show = false;
                }

                constexpr auto fmt = "{:<20}{:<10}{:<10}\n";

                std::cout << std::format(fmt, m_Name, m_Password, Get_StrAccess());
            }

        private:

            std::string_view Get_StrAccess()const {
                
                switch (m_Access)
                {
                case AccessLevel::NoAccess:     return "No Access";
                    
                case AccessLevel::LowAccess:    return "Low Access";
                    
                case AccessLevel::FullAccess:   return "Full Access"; 
                }// end switch

            }// end funciton

            void Serialize(std::ostream& out) {
                auto size = m_Name.size();
                out.write(reinterpret_cast<char*>(&size), sizeof(size));
                out.write(m_Name.data(), size);

                auto passsize = m_Password.size();
                out.write(reinterpret_cast<char*>(&passsize), sizeof(passsize));
                out.write(m_Password.data(), passsize);
            }// end function

            void Deserialize(std::istream& in) {
                auto size = 0;

                in.read(reinterpret_cast<char*>(&size), sizeof(size));
                m_Name.resize(size);
                in.read(m_Name.data(), size);

                auto passsize = 0;

                in.read(reinterpret_cast<char*>(&passsize), sizeof(passsize));
                m_Password.resize(passsize);
                in.read(m_Password.data(), passsize);



            }// end function

            void Title()const {
                constexpr auto fmt = "{:<20}{:<10}{:<10}\n";
                std::cout << std::format(fmt, "Name", "Password", "Access");
                std::cout << std::string(40, '-') << '\n';

            }
        private:

            AccessLevel m_Access;

            std::string m_Name, m_Password;
        };
    }// end namespace manager

} // end namespace studentManager

