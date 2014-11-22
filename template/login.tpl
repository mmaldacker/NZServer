<!DOCTYPE html>
<html lang="en" class="no-js">
{# head #}
<body>
{% header = {title = "Articles", abstract = "Some informative texts and tutorials"} %}
{# header #}

{% 
if method == "GET" then 
  if headers["Cookie"] and session.is_logged_in(headers["Cookie"]) then
%}
  {{ "Logged in!" }}
{% 
  else
%}
{{[[
<form action="" method="post">
  <fieldset>
    <legend>Login</legend>

      <label for="login">Username</label>
      <input type="text" name="login" cols="60" placeholder="Your login...">

      <label for="password">Password</label>
      <input type="password" name="password" cols="60">

      <input type="submit" value="Login" class="button">
  </fieldset>
</form>
]]}}
{% 
  end
elseif method == "POST" then 
  if session.login(post["login"], post["password"]) then
    cookie = session.get_session_cookie(post["login"])
    set_header("Set-Cookie", cookie)
%}
    {{ "Successful!" }}
{% 
  else 
%}
    {{ "Fail!" }}
{% 
  end 
end
%}

<script src="/file/js/default.js"></script>

</body>
</html>
