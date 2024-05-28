#include "miniRT.h"
#include "parser.h"

int check_duplicated(t_data *data)
{
    if (data->ambient->total != 1)
        return (printf(RED"Error!\nOnly one ambient light allowed\n"RST), KO);
    if (data->camera->total != 1)
        return (printf(RED"Error!\nOnly one camera allowed\n"RST), KO); // maybe more in the future
    if (data->light->total != 1)
        return (printf(RED"Error!\nOnly one light allowed\n"RST), KO); // maybe more in the future
    return (OK);
}
