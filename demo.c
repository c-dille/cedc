#include <networking/server/tcp> using std.TcpServer as TcpServer
#include <networking/server/http> using std.HttpServer, std.HttpResponse, std.HttpRequest as ...
#include "auth.ç"

auto tcpServer = new TcpServer(8080)
auto httpServer = new HttpServer(TcpServer)
auto pgLink = new OdbcClient(pgsql, 127.0.0.1)

httpServer.on('/bonjour', async lambda(req, resp ->
	reso.print "Bienvenue sur la cédille!"
))

httpServer.on('/login', async lambda(req, resp ->
	auto users = await pgLink.
		select * from user where email = resp.email and pw = hash(resp.pw)
	if (!users.length)
		return resp.print "Email or password incorect"
	return auth(resp, )
))

tcpServer.run()
