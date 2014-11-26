<!DOCTYPE html>
<html lang="en" class="no-js">
{# head #}
<body>
{% header = {title = "Login", abstract = ""} %}
{# header #}

<div class="container font-light">
    <div class="clear row">
        <h2 class="h3 font-light">Session</h2>
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
    <div class="row clear">
      <input type="text" name="login" cols="60" placeholder="Username">
      <input type="password" name="password" cols="60" placeholder="Password">
    </div>
    <div class="row clear">
      <input type="submit" value="Login" class="button">
    </div>
  </fieldset>
</form>
]]}}
{% 
  end
elseif method == "POST" then 
  if session.login(post["login"], post["password"]) then
    cookie = session.get_session_cookie(post["login"])
    template_engine.set_header("Set-Cookie", cookie)
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
  </div>
</div>

{# footer #}

<script src="/file/js/default.js"></script>

</body>
</html>
