#!/usr/bin/env python3
import sys

START_MARKER = "========== Test Starts ============"
END_MARKER = "========== Test Finished =========="

def main():
    started = False
    
    try:
        for line in sys.stdin:
            line = line.rstrip('\n')
            
            if not started:
                if START_MARKER in line:
                    started = True
                    print(line)
            else:
                print(line)
                
                if END_MARKER in line:
                    break
                    
    except KeyboardInterrupt:
        pass
    except BrokenPipeError:
        pass

if __name__ == "__main__":
    main()