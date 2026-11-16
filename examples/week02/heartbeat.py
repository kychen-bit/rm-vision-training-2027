#!/usr/bin/env python3
"""Training-only process: no robot hardware and no external network."""
from datetime import datetime
import time

print('rm-vision heartbeat started', flush=True)
while True:
    print('heartbeat', datetime.now().isoformat(timespec='seconds'), flush=True)
    time.sleep(5)
