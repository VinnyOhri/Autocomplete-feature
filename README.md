# Autocomplete-feature

Google Suggestions  and Gmail autocomplete logic in google search engine would be implemented as a Trie (prefix tree). Autocomplete feature is embedded in most softwares even in our UNIX shell, our coding environment, google search engine etc. In autocompletion we write only few characters and we get suggested with all words which have our written text as prefix.

1 Approach:
The first way is to DFS from the current prefix or node to get to all the possible words below. This approach is time-intensive due to its recursive nature and the user probably would not benefit when the Trie is large. Autocomplete features need to be quick as the user probably would have typed the next character by the time the logic would return results. The Gmail autocomplete Trie is client side and small. This approach should be enough.

How can we improve this?
The number of matches might just be too large so we have to be selective while displaying them. We can restrict ourselves to display only the relevant results. By relevant, we can consider the past search history and show only the most searched matching strings as relevant results.
Store another value for the each node where isleaf=True which contains the number of hits for that query search. For example if “hat” is searched 10 times, then we store this 10 at the last node for “hat”. Now when we want to show the recommendations, we display the top k matches with the highest hits.

2 Approach
The Google Suggest Trie is server-side and large. The DFS approach is time-intensive. Here is my take on it – the second way. For the Trie data structure of each node, a list for each node is required (or a set to avoid duplicates) which contains all the words formed while traversing it. While adding a word to the Trie, the list of every node lying on the path is updated with the remaining part of word. For example, if the Trie has ‘anon‘, ‘an‘, ‘a‘, the list of node ‘a’ would contain ‘non’ and ‘n’ (as ‘a-non’ and ‘a-n’ are words but not ‘no’ as ‘a-no’ is not a word) and the words ‘anon’ and ‘an’ can be retrieved from node ‘a’. The rough code is mostly same like the first post with slight changes shown below in blue. Although, this approach is space-intensive(takes a lot of space). For a word of length n, we have to store n-1 prefixes in Trie (for ‘anon’, we save ‘non’, ‘on’, ‘n’).

The disadvantage with Trie is that since it is a prefix data structure, a word can be looked up only through one of its prefixes. So, the only way to look up a word ‘calendar’ is through ‘c’, ‘ca’ etc. If it was a suffix data structure, a word ‘calendar’ can be looked up through any of its suffix like ‘dar’, ‘len’ etc. An example of suffix data structure would be something similar to autocomplete logic used in Mozilla Firefox’s Location bar.

Another example is to find the distinct words from a text file. At first, I thought of a Hashmap which acts like a boolean array for the words as index. In which case, the time required is O(n) and space required is that of the distinct words. With Trie, the solution is better and elegant in terms of space required (time required is O(n)). In case of words ‘anon’, ‘an’, ‘a’, the Trie formed (”-a–n-o-n) would just need space for a-n-o-n. Thus, the advantages of Trie would show over a Hashmap when many words have overlapping prefixes. Once the Trie is formed, a DFS would print the distinct words as follows.

//do DFS on the trie
StringBuilder sb = new StringBuilder()
dfs(root, sb)
void dfs(trieNode node, StringBuilder sb):
    sb.append(node.c)
    
    if (node.countWord > 0):
        print(sb)
    
    for (trieNode child : node.children)
        if (child != null):
            dfs(child, sb)
    
    sb.length = sb.length -1
