/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	loader
/**	[TODO]
 */
struct loader
{
	/// constructor
	loader();

	/// destructor
	~loader();

	///	open a file
	/**	open the file specified by _path and return it's ID or uint(-1) if failed
	 */
	uint open(const wchar * _path);

	///	check a file
	/**	check if the file specified by _ID is opened
	 */
	bool good(uint _ID) const;

	///	move the read position in a file
	/**	move the read position in the file specified by _ID by _offset relative
		to _from (0 - from begin, 1 - from current, 2 - from end). return current
		absolute position or uint(-1) if failed
	 */
	uint seek(uint _ID, sint _offset = 0, uint _from = 1);

	/// read from a file
	/**	read _length bytes from the file specified by _ID to _buffer
	 */
	uint read(uint _ID, handle _buffer, uint _length);

	/// close a file
	/**	close the file specified by _ID
	 */
	void close(uint _ID);

private:
	pool_<std::ifstream *> m_pool;
	//struct file { std::ifstream* stream_p; uint ID; };
	//array_<file> m_files;
	//array_<uint> m_free_IDs;
	//uint m_counter;
};