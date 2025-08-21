#include "../../execution/exec.h"

int	quote_checker(char c, int *sq, int *dq, int *cnt)
{
	if (c == '\'' && !(*dq))
	{
		*sq = !(*sq);
		if (cnt)
			(*cnt)--;
		return (1);
	}
	if (c == '"' && !(*sq))
	{
		*dq = !(*dq);
		if (cnt)
			(*cnt)--;
		return (1);
	}
	return (0);
}

void	write_val(char *dst, int *i, char *val)
{
	int	x;

	if (!val)
		return ;
	x = 0;
	while (val[x])
	{
		dst[*i] = val[x];
		(*i)++;
		x++;
	}
}

void	handle_exit_status(char *dst, t_exp_vars *vars)
{
	char	*status_str;

	status_str = ft_itoa(status_get());
	write_val(dst, &vars->i, status_str);
	vars->k = 0;
	while (vars->k < (int)ft_strlen(status_str))
	{
		vars->nmap[vars->f++] = '0';
		vars->k++;
	}
	vars->j += 2;
	vars->e += 2;
	free(status_str);
}

void	handle_variable_expansion(char *dst, char *src, \
	t_exp_vars *vars, t_env *env)
{
	int	d;

	vars->k = 0;
	while (src[++vars->j] && var_middle(src[vars->j]))
		vars->k++;
	vars->e += vars->k + 1;
	vars->key = ft_substr2(src, vars->j - vars->k, vars->k);
	vars->k = ft_strlen(env_val(vars->key, env));
	d = 0;
	while (d < vars->k)
	{
		vars->nmap[vars->f++] = '0';
		d++;
	}
	write_val(dst, &vars->i, env_val(vars->key, env));
}

void	fill_nmap_and_dst(char *dst, char *src, t_exp_vars *vars)
{
	vars->nmap[vars->f++] = vars->map[vars->e++];
	dst[vars->i++] = src[vars->j++];
}
