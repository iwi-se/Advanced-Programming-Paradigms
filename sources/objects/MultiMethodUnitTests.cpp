// MultiMethodUnitTests.cpp by Ulrich Eisenecker, March 18, 2025

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
// This code is based on Catch2 v3,
// therefore only the minimal header
// file for test macros is included.
// The C++ library path must be set
// accordingly for compilation and
// linking, and the Catch2Main and
// Catch2 libraries must be linked
// explicitly in exactly this order!

#include <iostream>
#include <typeinfo>
#include <string>
#include <sstream>
#include <iomanip> // Because of setprecision().

using namespace std;

using money_t = float;

class Account
{
   public:
      explicit Account(money_t amount):m_amount { amount }
      {}
      void credit(money_t amount)
      {
         m_amount += amount;
      }
      void debit(money_t amount)
      {
         m_amount -= amount;
      }
      [[nodiscard]] string balance() const
      {
         ostringstream os;
         os << setprecision(2) << fixed
            << m_amount << ' ' << currencyAbbreviation();
         return os.str();
      }
      virtual ~Account() = default;
   protected:
      [[nodiscard]] virtual string currencyAbbreviation() const = 0;
   private:
      money_t m_amount;
};

class AccountEUR: public Account
{
   public:
      using Account::Account;
   protected:
      [[nodiscard]] string currencyAbbreviation() const override
      {
         return "EUR";
      }
};

class AccountUSD: public Account
{
   public:
      using Account::Account;
   protected:
      [[nodiscard]] string currencyAbbreviation() const override
      {
         return "USD";
      }
};

void transfer(Account& source,Account& destination,money_t amount);

TEST_CASE("EUR")
{
   AccountEUR account { 500.50 };
   REQUIRE(account.balance() == "500.50 EUR");
   account.credit(99.50);
   REQUIRE(account.balance() == "600.00 EUR");
   account.debit(100);
   REQUIRE(account.balance() == "500.00 EUR");
}

TEST_CASE("USD")
{
   AccountUSD account { 500.50 };
   REQUIRE(account.balance() == "500.50 USD");
   account.credit(99.50);
   REQUIRE(account.balance() == "600.00 USD");
   account.debit(100);
   REQUIRE(account.balance() == "500.00 USD");
}

TEST_CASE("TRANSFER")
{
   AccountEUR eurAccount1 { 100 };
   AccountEUR eurAccount2 { 200 };
   AccountUSD usdAccount1 { 50 };
   AccountUSD usdAccount2 { 150 };
   SECTION("EUR2EUR")
   {
      transfer(eurAccount1,eurAccount2,50);
      REQUIRE(eurAccount1.balance() == "50.00 EUR");
      REQUIRE(eurAccount2.balance() == "250.00 EUR");
   }
   SECTION("EUR2USD")
   {
      transfer(eurAccount1,usdAccount1,50);
      REQUIRE(eurAccount1.balance() == "50.00 EUR");
      REQUIRE(usdAccount1.balance() == "104.50 USD");
   }
   SECTION("USD2USD")
   {
      transfer(usdAccount1,usdAccount2,25);
      REQUIRE(usdAccount1.balance() == "25.00 USD");
      REQUIRE(usdAccount2.balance() == "175.00 USD");
   }
   SECTION("USD2EUR")
   {
      transfer(usdAccount1,eurAccount1,25);
      REQUIRE(usdAccount1.balance() == "25.00 USD");
      REQUIRE(eurAccount1.balance() == "123.00 EUR");
   }
}

void transfer(Account& source,Account& destination,money_t amount)
{
   money_t convertedAmount { amount };
   if (typeid(source) == typeid(AccountEUR))
   {
      if (typeid(destination) == typeid(AccountUSD))
      {
         convertedAmount *= 1.09; 
      }
   }
   if (typeid(source) == typeid(AccountUSD))
   {
      if (typeid(destination) == typeid(AccountEUR))
      {
         convertedAmount *= 0.92; 
      }
   }
   source.debit(amount);
   destination.credit(convertedAmount);
}
