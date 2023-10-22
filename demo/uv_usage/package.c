typedef struct s_remote_package
{
	const char *url;
	float version;
} remote_package;

typedef struct s_package
{
	float version;
	remote_package *dependancies;
}	package;

make ()
{
/// todo ... also support other commands
}

package manifest()
{
	return (package) {
		.version = 1.0,
		.dependancies = (remote_package[1]){
			{
				.url = "github.com/test",
				.version = 1.1,
			}
		}
	};
}
