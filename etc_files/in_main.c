#include "../includes_exec/execute.h"

static void	init_term(void);

int	main(void)
{
	struct termios	term;

	printf("\033[37;1m");		// minishell 글씨체 변경
	tcgetattr(STDIN_FILENO, &term);				// 현재 shell의 출력 상태를 저장
	// init
	init_term();
	// parse
	// execute
	// free
	tcsetattr(STDIN_FILENO, TCSANOW, &term);	// 모든 것이 끝났으므로 다시 원상 복귀
	return (EXIT_SUCCESS);
}

static void	init_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);			// 해당 flag로 shell의 상태 변경
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
