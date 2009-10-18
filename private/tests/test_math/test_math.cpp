// test_math.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma comment(lib, "d3dx9")

//#pragma fenv_access(on)
//#pragma fp_contract(on)

#pragma float_control(precise, on)
#pragma fenv_access(off)

//template<typename _T> struct A {
//	A(_T &_t) : m_t(_t) { m_t.c++; }
//	~A() { m_t.c--; }
//private:
//	_T &m_t;
//};
//
//struct B {
//	B() : c(0) {}
//private:
//	friend A<B>;
//	int c;
//};

struct A {};

int _tmain(int argc, _TCHAR* argv[])
{
	typedef bk::vector_<bk::real, 3> real3;
	typedef bk::vector_<real3::column, 3> real3x3;

	real3 l_real3(1, 1, 1), l_a(2, 2, 2), l_b(3, 3, 3), l_c = l_a + l_b;

	l_a.add(l_a, l_c);
	l_c = l_b + l_b;

	real3x3 l_real3x3(real3(1, 0, 0),
					  real3(0, 1, 0),
					  real3(0, 0, 1));

	typedef bk::_vector_base::mul_<bk::vector_<bk::real, 3>::column, bk::vector_<bk::real, 3> >::result dot_type;
	dot_type l_dot;

/////////////

	const bk::uint l_count = 1000000;

	bk::rbig l_start;
	
	bk::r4x4 l_m0(
		bk::r1x4(1.f, 3.f, 3.f, 4.f),
		bk::r1x4(5.f, 6.f, 7.f, 8.f),
		bk::r1x4(1.f, 2.f, 3.f, 5.f),
		bk::r1x4(1.f, 2.f, 3.f, 4.f) 
	), l_m1;
	//l_m0 = bk::r4x4(
	//	bk::r1x4(1.f, 3.f, 3.f, 4.f),
	//	bk::r1x4(5.f, 6.f, 7.f, 8.f),
	//	bk::r1x4(1.f, 2.f, 3.f, 5.f),
	//	bk::r1x4(1.f, 2.f, 3.f, 4.f) 
	//	);

	bk::u16 l_oldcw, l_cw;

	__asm
	{
		fstcw	l_oldcw				;
		fwait						;
		mov		ax, l_oldcw			;
		or		ax, (2<<8)			;
//		and		ax, (0xffff^(3<<8))	;
		mov		l_cw, ax			;
		fldcw	l_cw				;
		fwait						;
	};

	//__control87_2(_PC_24, MCW_PC, 0, 0);
	//_controlfp(_PC_24, _MCW_PC);

	l_start = bk::sys_time();
	for (bk::uint i = 0; i < l_count; ++i)
	{
		bk::inverse(l_m0, l_m1);
		l_m0 = l_m1;
		//break;
	}

	std::cout << "Time 0: " << bk::sys_time() - l_start << "\n";

	D3DXMATRIX l_M0(
		1.f, 3.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		1.f, 2.f, 3.f, 5.f,
		1.f, 2.f, 3.f, 4.f 
	), l_M1;
	//D3DXMatrixIdentity(&l_M0);
	//l_M0._11 = 1.f; l_M0._12 = 3.f; l_M0._13 = 3.f; l_M0._14 = 4.f;
	//l_M0._21 = 5.f; l_M0._22 = 6.f; l_M0._23 = 7.f; l_M0._24 = 8.f;
	//l_M0._31 = 1.f; l_M0._32 = 2.f; l_M0._33 = 3.f; l_M0._34 = 5.f;
	//l_M0._41 = 1.f; l_M0._42 = 2.f; l_M0._43 = 3.f; l_M0._44 = 4.f;

	l_start = bk::sys_time();
	for (bk::uint i = 0; i < l_count; ++i)
	{
		D3DXMatrixInverse(&l_M1, 0, &l_M0);
		l_M0 = l_M1;
		//break;
	}

	std::cout << "Time 1: " << bk::sys_time() - l_start << "\n";

	D3DXMATRIX l_M = l_M0;

//	B l_b;
//	A<B> l_a(l_b);
//	
//	{
//	bk::r2x2 l_r2x2 = bk::minor<0, 2>(bk::r3x3_1);
//	std::cout << l_r2x2[0][0] << " " << l_r2x2[0][1] << "\n";
//	std::cout << l_r2x2[1][0] << " " << l_r2x2[1][1] << "\n";
//	std::cout << "\n";
//	}
//	{
//	bk::real l_d = bk::determinant(bk::r3x3(bk::r1x3_x,-bk::r1x3_z, bk::r1x3_y));
//	std::cout << l_d << "\n";
//	std::cout << "\n";
//	}
//	{
//	bk::r3x3 l_m(
//		bk::r1x3(4, 1, 3),
//		bk::r1x3(6, 2, 5),
//		bk::r1x3(7, 8, 9)
//	);
//	std::cout << l_m[0][0] << " " << l_m[0][1] << " " << l_m[0][2] << "\n";
//	std::cout << l_m[1][0] << " " << l_m[1][1] << " " << l_m[1][2] << "\n";
//	std::cout << l_m[2][0] << " " << l_m[2][1] << " " << l_m[2][2] << "\n";
//	std::cout << "\n";
//	bk::r3x3 l_a = l_m;
//	l_m = bk::inverse(l_m);
//	std::cout << l_m[0][0] << " " << l_m[0][1] << " " << l_m[0][2] << "\n";
//	std::cout << l_m[1][0] << " " << l_m[1][1] << " " << l_m[1][2] << "\n";
//	std::cout << l_m[2][0] << " " << l_m[2][1] << " " << l_m[2][2] << "\n";
//	std::cout << "\n";
//	l_m = l_a * l_m;
//	std::cout << l_m[0][0] << " " << l_m[0][1] << " " << l_m[0][2] << "\n";
//	std::cout << l_m[1][0] << " " << l_m[1][1] << " " << l_m[1][2] << "\n";
//	std::cout << l_m[2][0] << " " << l_m[2][1] << " " << l_m[2][2] << "\n";
//	std::cout << "\n";
//	}
//	{
//	bk::r1x3 l_b(-bk::r1x3_1); l_b = bk::r1x3_z - bk::r1x3_y;
//	bk::r3x3 l_r(bk::r1x3_x,-bk::r1x3_z, bk::r1x3_y); //l_r = ~l_r;
//	bk::real l_00 = l_b[0][0];
//	bk::uint l_count = 1000000;
//	bk::rbig l_time = bk::sys_time();
//	while(--l_count) {
//		l_b = l_b * ~l_r;
//		//l_b = ~(l_r * ~l_b);
//	}
//	l_time = bk::sys_time() - l_time;
//	//l_b[0][0] = bk::r1x3_1[0][2];
//	//bk::v3<bk::r1x3> l_v3(l_b);
//	//l_v3.x = bk::v3<const bk::r1x3>(bk::r1x3_0).z;
////	std::cout << l_v3.x << " " << l_v3.y << " " << l_v3.z << "\n";
//	std::cout << l_b[0][1] << " " << l_b[0][1] << " " << l_b[0][2] << "\n";
//	std::cout << l_time << "\n";
//	}	/**/

	return 0;
}

