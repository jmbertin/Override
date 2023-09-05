#!/usr/bin/env python3

import itertools
import sys

def create_pattern(length):
    """
    Generate a pattern of alternating characters and digits up to the specified length.
    Parameters:
    - length (int): The desired length of the pattern.
    Returns:
    - str: The generated pattern.
    """
    pattern = ''
    chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
    digits = '0123456789'
    for tuple in itertools.product(chars, digits):
        if len(pattern) < length:
            pattern += ''.join(tuple)
        else:
            break
    return pattern[:length]

def find_offset(pattern, address):
    """
    Find the offset of a given address within the pattern.
    Parameters:
    - pattern (str): The pattern in which to search.
    - address (str): The address to find.
    Returns:
    - int: The offset of the address within the pattern. Returns -1 if not found.
    """
    search_pattern = ''.join([chr(int(address[i-2:i], 16)) for i in range(len(address), 2, -2)])
    try:
        return pattern.index(search_pattern)
    except ValueError:
        return -1

if __name__ == "__main__":
    length = int(input('Enter the pattern length: '))
    pattern = create_pattern(length)
    print(f'Pattern: {pattern}')

    address = input('Enter the address to find: ')
    offset = find_offset(pattern, address)
    if offset != -1:
        print(f'Offset found at: {offset}')
    else:
        print('Pattern not found in the generated pattern')
