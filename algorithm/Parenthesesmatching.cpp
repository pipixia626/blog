class Solution {
public:
    /**
     * 
     * @param s string字符串 
     * @return bool布尔型
     */
    bool isValid(string s) {
        stack<char> sta;
      int countleft=0;
      int countright=0;
      char temp;
        for(int i=0;i<s.length();i++){
            if(s[i]=='('||s[i]=='['||s[i]=='{')
                countleft++;
            else
                countright++;
         }
        
        if(countleft!=countright){
            return false;
        }
        
        for(int i=0;i<s.length();i++){
            if(s[i]=='('||s[i]=='['||s[i]=='{'){
                sta.push(s[i]);
          }
            else if(s[i]==')'){
                temp=sta.top();
                sta.pop();
                if(temp!='(')
                      return false;
                else 
                    continue;
            }
            else if(s[i]==']'){
                temp=sta.top();
                sta.pop();
                if(temp!='[')
                    return false;
                else
                    continue;
           }
             else if(s[i]=='}'){
                temp=sta.top();
                sta.pop();
                if(temp!='{')
                    return false;
                else
                    continue;
           }
       }
        // write code here
        return true;
    }
};
