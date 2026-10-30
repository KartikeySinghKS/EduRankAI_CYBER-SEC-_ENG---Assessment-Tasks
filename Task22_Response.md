
Incident Response Plan: Accidentally Published Secret

Scenario: A developer published a configuration file containing an API credential to a public repository, then deleted the file five minutes later.

1. Immediate Response (Triage & Containment)

Revoke the Exposed Credential immediately: Treat the API key as fully compromised. Automated malicious bots scrape public GitHub repositories for secrets within seconds of a commit. Deleting the file after five minutes provides zero protection.

Generate and Inject a New Key: Create a replacement API credential and inject it into the application environment using a secure secrets manager (e.g., AWS Secrets Manager, HashiCorp Vault) or environment variables. Ensure it is not hardcoded into the repository.

Determine the Impact Radius: Identify the exact privileges, roles, and access scope associated with the exposed API key to establish what data or backend systems are potentially at risk.

2. Verification (Investigation)

Analyze API Access Logs: Audit the service provider's access logs for the compromised API key, focusing specifically on the time window starting from the commit timestamp to the moment the key was revoked.

Identify Anomalous Activity: Look for unusual API calls, unexpected IP addresses, or geographic locations that do not align with normal application behavior.

Assess Data Exfiltration or Manipulation: If the logs show the compromised key was used by an unauthorized actor, determine exactly what data was accessed, modified, or deleted to declare a formal data breach if necessary.

3. Eradication (Git History Cleanup)

Understand Git History: Simply deleting a file in a subsequent commit does not remove it from the repository's history; anyone can view the previous commit and extract the secret.

Purge the Secret: Use a tool like git filter-repo or BFG Repo-Cleaner to completely rewrite the repository's commit history and scrub the configuration file from all previous commits.

Force Push: Once the local history is cleaned, execute a git push --force to overwrite the public repository's history. (Note: The repository cache or forks may still contain the secret, which reinforces why immediate revocation in Step 1 is the only true fix).

4. Prevention (Long-Term Mitigation)

Implement Pre-Commit Hooks: Require developers to use local pre-commit hooks (like detect-secrets or Talisman) that scan code for high entropy strings and block commits containing potential credentials.

Enable Secret Scanning: Turn on GitHub Secret Scanning to automatically detect and alert administrators the moment a credential is inadvertently pushed to the remote repository.

Developer Training & Environment Configuration: Mandate the use of .gitignore for all configuration and .env files. Train the engineering team on secure secrets management practices to prevent hardcoding credentials in the future.
