#include "Polynomial.h"
#include <iostream>

ostream& operator<<(ostream &output, const Polynomial& p)
{
	Polynomial::Term* curr = p.head->next;
	int done = p.size;
	for (int start = 1; start <= done && curr != NULL; curr = curr->next, start++)
	{
		if (start == 1)  //First term should not include a binary operator
		{
			if (curr->power == 0)  //If x is raised to the 0, x = 1, do output terms coefficient
				output << curr->coeff;
			else if (curr->coeff == 1)  //If term's coefficient is one do not display the coefficient
			{
				if (curr->power == 1)  //If x is raised to the first power, no superscript needed, do not output ^1
					output << "x";
				else if (curr->power > 1)   //Output in the form of x^n
					output << "x^" << curr->power;
			}
			else if (curr->coeff > 1)  // Terms coefficient greater than 1
			{
				if (curr->power == 1)  //power == 1
					output << curr->coeff << "x"; //output x
				else if (curr->power > 1) //power greater than 1
					output << curr->coeff << "x^" << curr->power;  //output in the form of ax^n
			}
			else if (curr->coeff < 0)  //coefficient is negative
			{
				if (curr->coeff == -1) {
					if (curr->power == 1)
						output << "-x";  //output -x
					else if (curr->power > 1)
						output << "-x^" << curr->power;  //output in form -x^n
				}
				else if (curr->coeff < -1)
				{
					output << curr->coeff << "x^" << curr->power;  //output in form of -ax^n
				}
			}
		}
		else if (start != 1)  //must add a + or - before each term
		{
			if (curr->coeff < 0)  // add a - before each term
			{
				if (curr->power == 0)
					output << " - " << -(curr->coeff);
				else if (curr->coeff == -1)
				{
					if (curr->power == 1)
						output << " - " << "x";
					else if (curr->power > 1)
						output << " - " << "x^" << curr->power;
				}
				else if (curr->coeff < -1)
				{
					if (curr->power == 1)
						output << " - " << -(curr->coeff) << "x";
					else if (curr->power > 0)
						output << " - " << -(curr->coeff) << "x^" << curr->power;
				}
			}
			else if (curr->power == 0)  //add a + before each term
				output << " + " << curr->coeff;
			else if (curr->coeff == 1)
			{
				if (curr->power == 1)
					output << " + x";
				else if (curr->power > 1)
					output << " + x^" << curr->power;
			}
			else if (curr->coeff > 1)
			{
				if (curr->power == 1)
					output << " + " << curr->coeff << "x";
				else if (curr->power > 1)
					output << " + " << curr->coeff << "x^" << curr->power;
			}
		}
	}
	return output;
}

Polynomial::Polynomial()
{
	head = new struct Term;                 // 0th node is a dummy.
	head->next = head;
	head->prev = head;
	head->coeff = 0;
	head->power = 0;
	size = 0;
}

Polynomial::Polynomial(const Polynomial &rhs)
{
	head = new struct Term;   // create a dummy
	head->coeff = 0;
	head->power = 0;
	head->next = head;
	head->prev = head;
	size = 0;
	*this = rhs;                           // then assign rhs to this.
}

Polynomial::~Polynomial()
{
	while (size > 0)
		remove(head->next);				// delete items starting 1st
	delete head;				   // delete a dummy (at 0th).
	head = NULL;
}

int Polynomial::degree() const
{
	if (size == 0)  //if Polynomial has no terms return -1
		return -1;
	return head->next->power;  //otherwise return power of 1st Term (term of largest power)
}

double Polynomial::coefficient(const int power) const
{
	if (size == 0)  //if there are no Terms the coefficient is 0, return 0 signifying that no terms of power were found
		return 0;
	Term *p = head->next;
	for (int i = 1; p != NULL && p->power != power && i <= size; p = p->next, i++) {}
	return (p == NULL) ? 0 : p->coeff;  // return 0 if not found, coefficient of power term returned otherwise 
}

bool Polynomial::changeCoefficient(const double newCoefficient, const int power)
{
	if (size == 0)  //if no terms insert new term after head
		return insert(head, newCoefficient, power);  //return true if insert successfull, false otherwise
	Term *p = head->next; //create pointer to 1st term
	if (coefficient(power) == 0)  //if term of power doesn't exist insert it in proper position
	{
		if (degree() < power)  //if power greater than power of this Polynomial insert it at front
			return insert(head->next, newCoefficient, power);  //if insert successfull return true, else return false
		else if (degree() > power)  // if Polynomial of larger degree than power, insert power in proper place
		{
			for (int i = 1; p != NULL && p->power > power && i <= size; p = p->next, i++) {} //find proper place
			return insert(p, newCoefficient, power);  //return true if insert is successfull, false otherwise
		}
	}
	else  //Polynomial has term of degree power
	{
		if (newCoefficient == 0) // if newCoefficient == 0 remove term of degree power
		{

			for (int i = 1; p != NULL && p->power != power && i <= size; p = p->next, i++) {}  //find term with power power
			if (p->power == power)
				return remove(p);
		}
		else  //change coefficient of term of degree power
		{
			for (int i = 1; p != NULL && p->power != power && i <= size; i++, p = p->next) {}
			if (p->power == power)
				p->coeff = newCoefficient;
		}
	}
	p = NULL;
	return true;  //operation successfull
}

Polynomial Polynomial::operator+(const Polynomial& p) const
{
	Polynomial sum;  //create new Polynomial to hold sum and return
	Term* left = head->next;  //create pointer to first term of this
	Term* right = p.head->next;  //create pointer to first term of p
	int sizeL = size;    // get this.size
	int sizeR = p.size;  // get p.size
	int startL = 1;  //starting index of this
	int startR = 1;  //starting index of p
	Term* currentTerm = sum.head;  //create pointer to new Polynomial's head
	for (; (startL <= sizeL) && (startR <= sizeR); currentTerm = currentTerm->next)  //iterate over this and p and new polynomial
	{
		if (left->power > right->power)  //bigger term goes into new polynomial first
		{
			sum.changeCoefficient(left->coeff, left->power);  //insert term into new polynomial
			left = left->next;  //increment pointer
			startL++;   //increment index
		}
		else if (left->power < right->power)  //bigger term goes into new polynomial first
		{
			sum.changeCoefficient(right->coeff, right->power);  //insert term into new polynomial
			right = right->next;  //increment pointer
			startR++;  //increment index
		}
		else  //new coefficient based on sum of left and right power term
		{
			double newCoeff = right->coeff + left->coeff;  //sum left and right power term coefficients
			if (newCoeff != 0)
				sum.changeCoefficient(newCoeff, left->power);  //insert term into new polynomial 
			left = left->next;  //increment pointers
			right = right->next;
			startL++;  //increment indexs
			startR++;
		}
	}
	while (startL <= sizeL)  //finish off left side polynomial if neccessary
	{
		startL++;
		sum.changeCoefficient(left->coeff, left->power);
		left = left->next;
		currentTerm = currentTerm->next;
	}
	while (startR <= sizeR)  //finish off right side polynomial if neccessary
	{
		startR++;
		sum.changeCoefficient(right->coeff, right->power);
		right = right->next;
		currentTerm = currentTerm->next;
	}
	left = NULL;
	currentTerm = NULL;
	right = NULL;
	return sum;
}

Polynomial Polynomial::operator-(const Polynomial& p) const
{
	Polynomial sum; //create new Polynomial to hold sum and return
	Term* left = head->next;  //create pointer to first term of this
	Term* right = p.head->next;  //create pointer to first term of p
	int sizeL = size;  // get this.size
	int sizeR = p.size;  // get p.size
	int startL = 1;  //starting index of this
	int startR = 1;  //starting index of p
	Term* currentTerm = sum.head; //create pointer to new Polynomial's head
	for (; (startL <= sizeL) && (startR <= sizeR); currentTerm = currentTerm->next)  //iterate over this and p and new polynomial
	{
		if (left->power > right->power)  //bigger term goes into new polynomial first
		{
			sum.changeCoefficient(left->coeff, left->power); //insert term into new polynomial
			left = left->next; //increment pointer
			startL++; //increment index
		}
		else if (left->power < right->power)   //bigger term goes into new polynomial first
		{
			sum.changeCoefficient(-(right->coeff), right->power);
			right = right->next;  //increment pointer
			startR++; //increment index
		}
		else   //new coefficient based on sum of left and right power term
		{
			double newCoeff = left->coeff - right->coeff;  //sum left and right power term coefficients
			if (newCoeff != 0)
				sum.changeCoefficient(newCoeff, left->power);  // do not insert coefficients that == 0
			left = left->next;  //increment pointers
			right = right->next;
			startL++;  //increment index
			startR++;
		}
	}
	while (startL <= sizeL)  //finish off left
	{
		startL++;
		sum.changeCoefficient(left->coeff, left->power);
		left = left->next;
		currentTerm = currentTerm->next;
	}
	while (startR <= sizeR)  //finish off right
	{
		startR++;
		sum.changeCoefficient(-(right->coeff), right->power);
		right = right->next;
		currentTerm = currentTerm->next;
	}
	left = NULL;
	currentTerm = NULL;
	right = NULL;
	return sum;
}

bool Polynomial::operator==(const Polynomial& p) const
{
	Term* other = p.head->next;  //get first term of p
	Term* current = head->next;  //get first term of this
	if (size != p.size)  //if sizes dont match return false
	{
		return false;
	}
	for (int i = 1; other != NULL && current != NULL && i <= size; other = other->next,
		current = current->next, i++)  //iterate over both polynomials
	{
		if (current != NULL && other != NULL)
		{
			if (current->coeff != other->coeff) //if coefficients of same index don't match return false
				return false;
			if (current->power != other->power)  //if powers of same index don't match return false
				return false;
		}
	}
	other = NULL;
	current = NULL;
	return true;  //all indexs match
}

bool Polynomial::operator!=(const Polynomial& p) const
{

	return !(*this == p);  //if this == p return false, else true
}

Polynomial& Polynomial::operator=(const Polynomial& p)
{
	if (this != &p)    // avoid self-assignment
	{
		while (size > 0)
			remove(head->next);				// delete items starting 1st

		int index;
		Term* rnode;
		for (index = 1, rnode = p.head->next; rnode != NULL, index <= p.size;
			rnode = rnode->next, index++)  //add all elements of p to this
			changeCoefficient(rnode->coeff, rnode->power);
		rnode = NULL;
	}
	return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& p)
{
	Term* left = head->next;
	if (left == NULL && size != 0)
		size = 0;
	Term* right = p.head->next;
	int sizeL = size;
	int sizeR = p.size;
	int startL = 1;
	int startR = 1;
	Term* currentTerm = head->next;
	for (; (startL <= sizeL) && (startR <= sizeR); currentTerm = currentTerm->next)
	{
		if (left->power > right->power)
		{
			left = left->next;  //shift pointer to next term
			startL++;   //increment index
		}
		else if (left->power < right->power)
		{
			changeCoefficient(right->coeff, right->power);  //add rhs term to this
			right = right->next;  //shift pointer to next term
			startR++;  //increment index
		}
		else
		{
			double newCoeff = right->coeff + left->coeff;  //calculate new coeff
			left = left->next; 	//shift left pointer
			changeCoefficient(newCoeff, right->power);  //change this coeff
			right = right->next;  //shift right pointer
			startL++; //increment indexs
			startR++;
		}
	}
	while (startR <= sizeR)  //finish off rhs if neccessary
	{
		startR++;
		changeCoefficient(right->coeff, right->power);
		right = right->next;
		currentTerm = currentTerm->next;
	}

	left = NULL;
	right = NULL;
	currentTerm = NULL;
	return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& p)
{
	Term* left = head->next;
	if (left == NULL && size != 0)
		size = 0;
	Term* right = p.head->next;
	int sizeL = size;
	int sizeR = p.size;
	int startL = 1;
	int startR = 1;
	Term* currentTerm = head->next;
	for (; (startL <= sizeL) && (startR <= sizeR); currentTerm = currentTerm->next)
	{
		if (left->power > right->power)
		{
			left = left->next;  //shift pointer to next term
			startL++; //update index
		}
		else if (left->power < right->power)
		{
			changeCoefficient(-(right->coeff), right->power);  //add term
			right = right->next;  //right pointer point to next term
			startR++;  //update index
		}
		else
		{
			double newCoeff = left->coeff - right->coeff;  //calculate new coefficient
			left = left->next;
			changeCoefficient(newCoeff, right->power);   //change old coefficient to new coefficient
			 //shift pointers to next terms
			right = right->next;
			startL++;  //update indexs
			startR++;
		}
	}
	while (startR <= sizeR)  //finish off right hand Polynomial if neccessary
	{
		startR++;
		changeCoefficient(-(right->coeff), right->power);
		right = right->next;
		currentTerm = currentTerm->next;
	}

	left = NULL;
	right = NULL;
	currentTerm = NULL;
	return *this;
}

bool Polynomial::insert(Term* prev, const double newCoefficient, const int power)
{
	if (prev == NULL)//Insert fails
		return false;
	Term* newTerm = new Term;  //create new Term to insert
	newTerm->coeff = newCoefficient;
	if (newCoefficient == 0)
	{
		cout << "error can not insert term with coefficient = to 0!" << endl;
		return false;
	}
	newTerm->power = power;
	if (power < 0)
	{
		cout << "error can not insert term with power < 0" << endl;
		return false;
	}
	// insert newTerm before prev
	if (prev == head && size == 0)
	{
		// insert newTerm between head and 1st term
		newTerm->next = head->next;
		head->next->prev = newTerm;
		head->next = newTerm;
		newTerm->prev = head;
	}
	else if (size > 0 && prev == head)
	{
		//insert newTerm after last term
		newTerm->prev = head->prev;
		newTerm->next = head;
		head->prev->next = newTerm;
		head->prev = newTerm;
	}
	else
	{
		// insert newTerm before previous
		prev->prev->next = newTerm;
		newTerm->prev = prev->prev;
		newTerm->next = prev;
		prev->prev = newTerm;
	}
	size++; //increment size
	newTerm = NULL;
	return true;
}

bool Polynomial::remove(Term* pos)
{
	if (pos == NULL)
		return false;
	if (pos->prev != NULL)   // fix pointers
		pos->prev->next = pos->next;
	if (pos->next != NULL)
		pos->next->prev = pos->prev;
	delete pos;            // deallocate
	pos = NULL;
	size--;
	return true;
}
