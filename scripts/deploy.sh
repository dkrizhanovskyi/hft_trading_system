# scripts/deploy.sh
#!/bin/bash
set -e
scp -r build/* user@server:/path/to/deploy/
ssh user@server "cd /path/to/deploy && ./HFTTradingSystem"
echo "Deployment completed successfully!"
