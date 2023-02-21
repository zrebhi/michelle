// #include "../includes/minishell.h"

// typedef struct s_testlist
// {
// 	char            	**full_cmd;
// 	int             	infile;
// 	int	            	outfile;
//     struct s_cmdlist	*next;
// }		                t_testlist;

// t_testlist	*ft_lstnew_test(void)
// {
// 	t_testlist	*new;

// 	new = malloc(sizeof(*new));
// 	if (!new)
// 		return (0);
// 	new->infile = 0;
// 	new->outfile = 1;
// 	new->next = 0;
// 	return (new);
// }

// t_testlist	*ft_testlast(t_testlist *lst)
// {
//     t_testlist *temp;

// 	if (!lst)
// 		return (NULL);
//     temp = lst;
// 	while (temp->next)
// 		temp = temp->next;
// 	return (temp);
// }

// void	ft_testadd_back(t_testlist *lst, t_testlist *new)
// {
// 	t_testlist	*temp;

// 	if (lst == NULL)
// 		lst = new;
// 	else
// 	{
// 		temp = ft_cmdlast((lst));
// 		temp->next = new;
// 	}
// }

// void	ft_newnode(t_cmdlist *test)
// {
// 	t_cmdlist *new;
	
// 	new = ft_cmdnew();
// 	ft_cmdadd_back(test, new);
// }

// void    ft_assign_value(t_testlist *test)
// {
//     test->infile = 2;
//     test->outfile = 3;
// }

// int main()
// {
//     t_testlist  *test;
    
//     test = ft_lstnew_test();
//     temp = test;
//     printf("infile : %d - outfile : %d\n", test->infile, test->outfile);
//     ft_assign_value(test);
//     printf("infile : %d - outfile : %d\n", test->infile, test->outfile);
//     return (0);
// }