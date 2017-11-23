#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 
'''
class Account(object):
    num_accounts = 0

    def __init__(self,name,balance):
        self.name = name
        self.balance = balance
        Account.num_accounts += 1

    def __del__(self):
        Account.num_accounts -= 1

    def deposit(self,amt):
        self.balance = self.balance + amt

    def withdraw(self,amt):
        self.balance = self.balance - amt

    def inquiry(self):
        return self.balance


import random

class EvilAccount(Account):
    def __init__(self,name,balance,evilfactor):
        Account.__init__(self,name,balance)
        self.evilfactor = evilfactor
        
    def inquiry(self):
        if random.randint(0,4) == 1:
            return self.balance * self.evilfactor
        else:
            return self.balance


class MoreEvilAccount(EvilAccount):
    def deposit(self,amount):
        self.withdraw(5.00)
        EvilAccount.deposit(self,amount)

