#include "miniRT.h"

t_obj	*find_last(t_obj **obj)
{
	t_obj	*temp;

	if (!*obj)
		return (*obj);
	temp = *obj;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
