// test_watch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct A
{
	bk::sint2 b;
	void set_c(bk::sint2 _c) { m_c = _c; }
	bk::sint2 get_c() const { return m_c; }
	static bk::sint d;
	static bk::sint get_e() { return m_e; }
private:
	bk::sint2 m_c;
	static bk::sint m_e;
};
bk::sint A::d = 0;
bk::sint A::m_e = 0;

struct F : A
{
	virtual int vF() {return 0;}
};

bk::sint2 get_g()
{
	return bk::sint2(3, 4);
}

int run_http_server(bk::watch &_watch)
{
	//----------------------
	// Initialize Winsock.
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR) {
		printf("Error at WSAStartup()\n");
		return 0;
	}

	//----------------------
	// Create a SOCKET for listening for
	// incoming connection requests.
	SOCKET ListenSocket;
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}

	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	hostent* localHost = gethostbyname("");
	char* localIP = inet_ntoa (*(struct in_addr *)*localHost->h_addr_list);
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(localIP);
	service.sin_port = htons(1904);

	if (bind( ListenSocket, 
		(SOCKADDR*) &service, 
		sizeof(service)) == SOCKET_ERROR) {
		printf("bind() failed.\n");
		closesocket(ListenSocket);
		return 0;
	}

	//----------------------
	// Listen for incoming connection requests.
	// on the created socket
	if (listen( ListenSocket, 1 ) == SOCKET_ERROR) {
		printf("Error listening on socket.\n");
		return 0;
	}

	//----------------------
	// Create a SOCKET for accepting incoming requests.
	SOCKET AcceptSocket;
	printf("Waiting for client to connect...\n");

	//----------------------
	// Accept the connection.
	while(1) {
		AcceptSocket = SOCKET_ERROR;
		while( AcceptSocket == SOCKET_ERROR ) {
			AcceptSocket = accept( ListenSocket, NULL, NULL );
		}
		printf("Client connected.\n");
		const int buf_max = 1024 * 10;
		char recv_buf[buf_max];
		int recv_len = recv(AcceptSocket, recv_buf, buf_max, 0);
		if(recv_len != SOCKET_ERROR) {
			recv_buf[recv_len] = 0;
			bk::astring request = recv_buf, response;
			bk::array_<bk::s8> send_buf;
			//if(strncmp(recv_buf, "GET ", 4) == 0) {
			if(request.find("GET ") == 0) {
				request.erase(0, 4);
				bk::astring URL = request.substr(0, request.find(' ', 0));
				bk::uint IDR = bk::bad_ID; LPCWSTR IDR_type = 0;
				if (URL == "/" || URL == "/index.html") { IDR = IDR_HTML1; IDR_type = RT_HTML; }
				else if (URL == "/dtree.css") { IDR = IDR_HTML2; IDR_type = RT_HTML; }
				else if (URL == "/dtree.js") { IDR = IDR_HTML3; IDR_type = RT_HTML; }
				else { IDR = IDR_GIF1; IDR_type = L"GIF"; }
				if(IDR != bk::bad_ID) {
					HRSRC l_res_info = FindResourceW(0, MAKEINTRESOURCE(IDR), IDR_type);
					if (l_res_info != 0) {
						DWORD l_res_size = SizeofResource(0, l_res_info);
						HGLOBAL l_res = LoadResource(0, l_res_info);
						response = "HTTP/1.1 200 OK\r\n\r\n";
						send_buf.assign(response.c_str(), response.c_str() + response.length());
						send_buf.insert(send_buf.end(), (const char*)l_res, (const char*)l_res + l_res_size);
//						response.append((const char*)l_res, l_res_size);
						//struct _l {static void format(const bk::watch::varaible &_v, bk::astring &_s) {
						//	_s += "<tr><td width=5 valign=\"top\"";
						//	if (_v.member_count() > 0) _s += "<font size=-1 face=\"Arial\">+</font>";
						//	_s += "</td><td>";
						//	bk::astring l_str;
						//	l_str += _v.name();
						//	l_str += " - ";
						//	l_str += _v.type_name();
						//	bk::astring l_v = _v.print();
						//	if (l_v != "") l_str += " " + l_v;
						//	_s += "<div><font size=-1 face=\"Arial\">";
						//	_s += l_str;
						//	_s += "</font></div>";
						//	if (_v.member_count() > 0) {
						//		_s += "<table cellspacing=0 cellpadding=0 width=100%><tr><td width=5></td><td><table cellspacing=0 cellpadding=0 width=100%>";
						//		for (bk::uint i = 0, s = _v.member_count(); i < s; ++i) _l::format(_v.get_member(i), _s);
						//		_s += "</table></tr></table>";
						//	}
						//	_s += "</td></tr>";
						//}};
						//send_buf += "<table cellspacing=0 cellpadding=0 width=100%>";
						//for (bk::uint i = 0, s = _watch.global_count(); i < s; ++i) {
						//	_l::format(_watch.get_global(i), send_buf);
						//}
						//send_buf += "</table>";
						printf("Response: 200 Ok.\n");
					} else {
						response = "HTTP/1.1 404 Not Found\r\n\r\n";
						send_buf.assign(response.c_str(), response.c_str() + response.length());
						printf("Response: 404 Not Found.\n");
					}
				} else {
					response = "HTTP/1.1 404 Not Found\r\n\r\n";
					send_buf.assign(response.c_str(), response.c_str() + response.length());
					printf("Response: 404 Not Found.\n");
				}
			} else {
				response = "HTTP/1.1 501 Not Implemented\r\n\r\n";
				send_buf.assign(response.c_str(), response.c_str() + response.length());
				printf("Response: 501 Not Implemented.\n");
			}
			send(AcceptSocket, &send_buf[0], (int)send_buf.size(), 0);
		}
		closesocket(AcceptSocket);
		//ListenSocket = AcceptSocket;
		//break;
	}

	WSACleanup();

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int (F::*Fm)() = &F::vF;
//	void* ptr = *(void**)&F::vF;

	bk::watch l_watch;

	l_watch.add_type_<bk::sint>("sint");

	struct _sint2 {
		static inline bk::sint get_x(const bk::sint2 &_o) { return _o.x(); }
		static inline void set_x(bk::sint2 &_o, const bk::sint &_v) { _o.x() = _v; }
		static inline bk::sint get_y(const bk::sint2 &_o) { return _o.y(); }
		static inline void set_y(bk::sint2 &_o, const bk::sint &_v) { _o.y() = _v; }
	};
	l_watch.add_type_<bk::sint2>("sint2")
		.add_member(&_sint2::get_x, "x")
		.add_member(&_sint2::set_x, "x")
		.add_member(&_sint2::get_y, "y")
		.add_member(&_sint2::set_y, "y")
	;

	l_watch.add_type_<A>("A")
		.add_member(&A::b, "b")
		.add_member(&A::get_c, "c")
		.add_member(&A::set_c, "c")
		.add_member(&A::d, "d")
		.add_member(&A::get_e, "e")
	;

	l_watch.add_type_<F>("F")
		.add_base_<A>()
	;

	F f; f.b = bk::sint2(5, 6); f.set_c(bk::sint2(7, 8));
	bk::sint i = 2;

	bk::watch::varaible l_vi = l_watch.add_global(&i, "i");
	bk::watch::varaible l_vf = l_watch.add_global(&f, "f");
	bk::watch::varaible l_vg = l_watch.add_global(&get_g, "g");

	bk::sint i0 = l_vi.get_<bk::sint>();
	F f0 = l_vf.get_<F>();
	bk::sint2 g0 = l_vg.get_<bk::sint2>();

	bk::watch::varaible l_vf_c = l_vf["c"];

	bk::sint2 fc0 = l_vf_c.get_<bk::sint2>();

	bk::watch::varaible l_vf_c_x = l_watch.find_varaible("f::c::x");

	bk::sint fb0 = l_vf_c_x.get_<bk::sint>();

	run_http_server(l_watch);

	return 0;
}

