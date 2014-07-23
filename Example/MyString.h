//=============================================================================

#ifndef MyString_H
#define MyString_H

//=============================================================================
class MyString {
public:

  class InvalidStringException{};
  
  MyString();
  MyString(std::string str);

  ~MyString();

  int length() const;
  bool valid() const;
  
private:

  bool m_valid;
  std::string m_str;
};

//=============================================================================
MyString::MyString()
  : m_valid(false),
    m_str()
{
}

//=============================================================================
MyString::MyString(std::string str)
  : m_valid(true),
    m_str(str)
{
}

//=============================================================================
MyString::~MyString()
{
}

//=============================================================================
int MyString::length() const
{
  if (!m_valid) {
    throw InvalidStringException();
  }
  return static_cast<int>(m_str.length());
}

//=============================================================================
bool MyString::valid() const
{
  return m_valid;
}

#endif
