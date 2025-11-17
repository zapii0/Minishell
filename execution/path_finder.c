/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:11:21 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/16 09:19:11 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_matrix(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	*path_env_valider(t_env *env, char *cmd)
{
	char	**path;
	char	*temp_val;
	char	*final_path;
	int		i;

	i = 0;
	path = ft_split(save_env_value("PATH", env), ':');
	printf("%s", path[i]);
	temp_val = ft_strjoin("/", cmd);
	if (!path)
		return (NULL);
	while (path[i])
	{
		final_path = ft_strjoin(path[i], temp_val);
		if (access(final_path, X_OK | F_OK) == 0)
			return (free_matrix(path), free(temp_val), final_path);
		free(final_path);
		i++;
	}
	free_matrix(path);
	return (free(temp_val), ft_strdup(cmd));
}

char	*path_joiner(const char *path1, const char *path2)
{
	char	*connect;
	char	*new_path;

	connect = ft_strjoin(path1, "/");
	new_path = ft_strjoin(connect, path2);
	free(connect);
	return (new_path);
}

char	*check_valid_path(const char *dir_name, const char *file_name)
{
	char			*path;
	DIR				*dir;
	struct dirent	*file;

	dir = opendir(dir_name);
	if (dir == NULL)
		return (NULL);
	file = readdir(dir);
	while (file)
	{
		if (strcmp(file->d_name, file_name) == 0)
			path = path_joiner(dir_name, file->d_name);
	}
	closedir(dir);
	return (path);
}
