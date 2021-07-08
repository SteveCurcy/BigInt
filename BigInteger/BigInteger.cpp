#include "BigInteger.h"
using namespace std;

int cmp(const string& a, const string& b, int len = 0) {
    int len_a = a.length(), len_b = b.length(), sign = 1;
    if (len == 0) {
        if (a[len_a-1] != '-' && b[len_b-1] == '-') return 1;
        if (a[len_a-1] == '-' && b[len_b-1] != '-') return -1;
        if (a[len_a-1] == '-' && b[len_b-1] == '-') len_a--, len_b--, sign = -1;
        if (len_a != len_b) return (len_a - len_b) * sign;
        len = len_a;
    }
    len--;
    while (len >= 0 && a[len] == b[len]) len--;
    if (len < 0) return 0;
    return (a[len]-b[len])*sign;
}

int ston(const string& str) {
    int len = str.length(), i = 0, ans = 0, index = 1, sign = 0;
    if (str[len-1] == '-') sign = 1, len--;
    for (i = 0; i < len; i++) {
        ans += (str[i]-'0') * index;
        index *= 10;
    }
    return ans;
}

BigInt BigInt::mutiply(const BigInt& tmpa, const BigInt& tmpb) {
    BigInt a(tmpa), b(tmpb);
    int a_len = a.val.length(), b_len = b.val.length(), tar_len;
    char sign = '+';
    if (a.val[a_len-1] == '-' && b.val[b_len-1] == '-') {
        a.val.pop_back();   b.val.pop_back();
        a_len--;    b_len--;
    } else if (a.val[a_len-1] == '-' && b.val[b_len-1] != '-') {
        a.val.pop_back();   a_len--;    sign = '-';
    } else if (a.val[a_len-1] != '-' && b.val[b_len-1] == '-') {
        b.val.pop_back();   b_len--;    sign = '-';
    }
    if (a_len <= 3 && b_len <= 3) {
        int ans = ston(a.val) * ston(b.val);
        BigInt result;
        if (ans == 0) result.val.push_back('0');
        else {
            while (ans) {
                result.val.push_back('0'+(ans%10));
                ans /= 10;
            }
            if (sign == '-') result.val.push_back('-');
        }
        return result;
    }
    if (a_len > b_len) {
        tar_len = (a_len+1) >> 1;
        if (b_len <= tar_len) {
            BigInt AC, BC, tmp;
            tmp.val = a.val.substr(tar_len, a_len-tar_len);
            AC = mutiply(tmp, b);
            AC.val.insert(0, tar_len, '0');
            tmp.val = a.val.substr(0, tar_len);
            BC = mutiply(tmp, b);
            AC = AC+BC;
            if (sign == '-') AC.val.push_back('-');
            return AC;
        }
        BigInt AC, BD, MID, A, C, B, D;
        A.val = a.val.substr(tar_len, a_len-tar_len), C.val = b.val.substr(tar_len, b_len-tar_len);
        B.val = a.val.substr(0, tar_len), D.val = b.val.substr(0, tar_len);
        AC = mutiply(A, C);
        BD = mutiply(B, D);
        MID = AC + BD + mutiply(A-B, D-C);
        AC.val.insert(0, tar_len << 1, '0');
        MID.val.insert(0, tar_len, '0');
        AC = AC + MID + BD;
        if (sign == '-') AC.val.push_back('-');
        return AC;
    } else {
        tar_len = (b_len+1) >> 1;
        if (a_len <= tar_len) {
            BigInt AC, BC, tmp;
            tmp.val = b.val.substr(tar_len, b_len-tar_len);
            AC = mutiply(tmp, a);
            AC.val.insert(0, tar_len, '0');
            tmp.val = b.val.substr(0, tar_len);
            BC = mutiply(tmp, a);
            AC = AC+BC;
            if (sign == '-') AC.val.push_back('-');
            return AC;
        }
        BigInt AC, BD, MID, A, C, B, D;
        A.val = a.val.substr(tar_len, a_len-tar_len), C.val = b.val.substr(tar_len, b_len-tar_len);
        B.val = a.val.substr(0, tar_len), D.val = b.val.substr(0, tar_len);
        AC = mutiply(A, C);
        BD = mutiply(B, D);
        MID = AC + BD + mutiply(A-B, D-C);
        AC.val.insert(0, tar_len << 1, '0');
        MID.val.insert(0, tar_len, '0');
        AC = AC + MID + BD;
        if (sign == '-') AC.val.push_back('-');
        return AC;
    }
}

BigInt::BigInt(const string& str) {
    int i = 0, len = str.length();
    char sign;
    if (str[0] == '-') sign = '-', i++;
    else if (str[0] == '+') sign = '+', i++;
    else sign = '+';
    while (i < len && str[i] == '0') i++;
    if (i >= len) val.push_back('0');
    else {
        len--;
        while (len >= i) val.push_back(str[len--]);
        if (sign == '-') val.push_back('-');
    }
}

BigInt::BigInt(const BigInt& obj) {
    val = obj.val;
}

BigInt::BigInt(const char* str) {
    int i = 0, len = strlen(str);
    char sign;
    if (str[0] == '-') sign = '-', i++;
    else if (str[0] == '+') sign = '+', i++;
    else sign = '+';
    while (i < len && str[i] == '0') i++;
    if (i >= len) val.push_back('0');
    else {
        len--;
        while (len >= i) val.push_back(str[len--]);
        if (sign == '-') val.push_back('-');
    }
}

BigInt BigInt::operator+ (const BigInt& obj) {
    string result("");
    int this_len = val.length(), obj_len = obj.val.length(), i, carry = 0, tmp, swap = 0;
    char sign;
    if ((val[this_len-1] == '-' && obj.val[obj_len-1] == '-') || (val[this_len-1] != '-' && obj.val[obj_len-1] != '-')) {
        if (val[this_len-1] == '-' && obj.val[obj_len-1] == '-') {sign = '-'; this_len--; obj_len--;}
        else sign = '+';
        for (i = 0; i < this_len && i < obj_len; i++) {
            tmp = val[i] - '0' + obj.val[i] - '0' + carry;
            result.push_back('0' + (tmp%10));
            carry = tmp/10;
        }
        if (this_len > obj_len) {
            while (i < this_len) {
                tmp = val[i] - '0' + carry;
                result.push_back('0' + (tmp%10));
                carry = tmp/10;
                i++;
            }
        } else {
            while (i < obj_len) {
                tmp = obj.val[i] - '0' + carry;
                result.push_back('0' + (tmp%10));
                carry = tmp/10;
                i++;
            }
        }
        if (carry) result.push_back('0' + carry);
        if (sign == '-') result.push_back('-');
    } else {
        int cmp_val;
        if (val[this_len-1] == '-') {
            /* this number is negative */
            this_len--;
            if (this_len > obj_len || (this_len == obj_len && (cmp_val = cmp(val, obj.val, this_len)) > 0)) {
                sign = '-';
            } else if (this_len == obj_len && cmp_val == 0) {
                result = "0"; sign = '+';
            } else {
                sign = '+'; swap = 1;
            }
        } else {
            obj_len--;
            if (this_len > obj_len || (this_len == obj_len && (cmp_val = cmp(val, obj.val, this_len)) > 0)) {
                sign = '+';
            } else if (this_len == obj_len && cmp_val == 0) {
                result = "0"; sign = '+';
            } else {
                sign = '-'; swap = 1;
            }
        }
        if (result == "0") ;
        /* compute the value */
        else if (swap) {
            for (i = 0; i < this_len; i++) {
                tmp = obj.val[i]-val[i]-carry;
                if (tmp < 0) {
                    carry = 1; tmp += 10;
                } else carry = 0;
                result.push_back(tmp+'0');
            }
            while (i < obj_len) {
                tmp = obj.val[i]-'0'-carry;
                if (tmp < 0) {
                    carry = 1; tmp += 10;
                } else carry = 0;
                result.push_back(tmp+'0');
                i++;
            }
        } else {
            for (i = 0; i < obj_len; i++) {
                tmp = val[i]-obj.val[i]-carry;
                if (tmp < 0) {
                    carry = 1; tmp += 10;
                } else carry = 0;
                result.push_back(tmp+'0');
            }
            while (i < this_len) {
                tmp = val[i]-'0'-carry;
                if (tmp < 0) {
                    carry = 1; tmp += 10;
                } else carry = 0;
                result.push_back(tmp+'0');
                i++;
            }
        }
        while (result.back() == '0' && result.length() > 1) result.pop_back();
        if (sign == '-') result.push_back('-');
    }
    BigInt ret;
    ret.val = result;
    return ret;
}

BigInt BigInt::operator- (const BigInt& tmp) {
    BigInt obj = tmp;
    int this_len = val.length(), obj_len = obj.val.length();
    char sign;
    if (obj.val[obj_len-1] != '-') {
        obj.val.push_back('-');
        obj = *this + obj;
    } else {
        obj.val.pop_back();
        obj = *this + obj;
    }
    return obj;
}

BigInt BigInt::operator* (const BigInt& obj) {
    return mutiply(*this, obj);
}

BigInt BigInt::operator/ (const BigInt& obj) {
    BigInt ans, tmp(*this), tmp_obj(obj), byp("1");
    int len = val.length(), obj_len = obj.val.length(), sign = 1, offset, cnt = 0;
    if (val[len-1] != '-' && obj.val[obj_len-1] == '-') obj_len--, tmp_obj.val.pop_back(), sign = -1;
    if (val[len-1] == '-' && obj.val[obj_len-1] != '-') len--, tmp.val.pop_back(), sign = -1;
    if (val[len-1] == '-' && obj.val[obj_len-1] == '-') len--, obj_len--, tmp.val.pop_back(), tmp_obj.val.pop_back();
    if (tmp < tmp_obj) return ans;
    offset = len-obj_len; tmp_obj.val.insert(0, offset, '0'); byp.val.insert(0, offset, '0');
    while (tmp >= obj) {
        while (tmp >= tmp_obj) {
            cnt++; tmp = tmp-tmp_obj;
        }
        if (cnt) {
            byp.val.pop_back();
            byp.val.push_back('0'+cnt);
            ans = ans + byp;
            cnt = 0;
        }
        tmp_obj.val.erase(0, 1);
        byp.val.erase(0, 1);
    }
    if (sign == -1) ans.val.push_back('-');
    return ans;
}

BigInt BigInt::operator% (const BigInt& obj) {
    BigInt ans, tmp(*this), tmp_obj(obj), byp("1");
    int len = val.length(), obj_len = obj.val.length(), offset, cnt = 0;
    if (val[len-1] == '-') {
        tmp.val.pop_back(); len--;
    }
    if (obj,val[obj_len-1] == '-') {
        tmp_obj.val.pop_back(); obj_len--;
    }
    if (tmp < tmp_obj) return tmp;
    offset = len-obj_len; tmp_obj.val.insert(0, offset, '0'); byp.val.insert(0, offset, '0');
    while (tmp >= obj) {
        while (tmp >= tmp_obj) {
            cnt++; tmp = tmp-tmp_obj;
        }
        if (cnt) {
            byp.val.pop_back();
            byp.val.push_back('0'+cnt);
            ans = ans + byp;
            cnt = 0;
        }
        tmp_obj.val.erase(0, 1);
        byp.val.erase(0, 1);
    }
    return tmp;
}

BigInt& BigInt::operator+= (const BigInt& obj) {
    return *this = (*this)+obj;
}

BigInt& BigInt::operator-= (const BigInt& obj) {
    return *this = (*this)-obj;
}

BigInt& BigInt::operator*= (const BigInt& obj) {
    return *this = (*this)*obj;
}

BigInt& BigInt::operator/= (const BigInt& obj) {
    return *this = (*this)/obj;
}

BigInt& BigInt::operator%= (const BigInt& obj); {
    return *this = (*this)%obj;
}

BigInt& BigInt::operator= (const BigInt& obj) {
    val = obj.val;
    return *this;
}

bool BigInt::operator> (const BigInt& obj) {
    return cmp(this->val, obj.val) > 0;
}

bool BigInt::operator>= (const BigInt& obj) {
    return cmp(this->val, obj.val) >= 0;
}

bool BigInt::operator< (const BigInt& obj) {
    return cmp(this->val, obj.val) < 0;
}

bool BigInt::operator<= (const BigInt& obj) {
    return cmp(this->val, obj.val) <= 0;
}

bool BigInt::operator== (const BigInt& obj) {
    return cmp(this->val, obj.val) == 0;
}

ostream& operator<< (ostream& output, const BigInt& obj) {
    int len = obj.val.length()-1;
    while (len >= 0) output << obj.val[len--];
    return output;
}